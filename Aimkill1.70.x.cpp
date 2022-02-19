"BT_Aimskill Weapons",//0



MemoryPatch TakeDamege;
MemoryPatch TakeSkill;



struct {
bool AimKillWeapons = false;
bool aimkill = false;
} MazeTeam;



case 0:
MazeTeam.AimKillWeapons = !MazeTeam.AimKillWeapons;
MazeTeam.aimkill = !MazeTeam.aimkill;
break;


if(MazeTeam.AimKillWeapons){
    MazeTeam.aimkill = true;
    TakeDamege.Modify();
    TakeSkill.Modify();
        } else {
    MazeTeam.aimkill = false;
    TakeDamege.Restore();
    TakeSkill.Restore();
}





//Aimkill
enum FireMode {
    MANUL,  // 0
    AUTO    // 1
};

enum FireStatus {
    NONE,   //0
    FIRING, //1
    CANCEL //2
};





enum Hit {
    Head,  //0
    Neck,  //1
    Chest, //2
    Hips,  //3
    LeftArm, //4
    LeftForeArm, //5
    RightArm, //6
    RightForeArm, //7
    LeftUpLeg, //8
    LeftLeg, //9
    RightUpLeg, //10
    RightLeg, //11
    LeftFoot, //12
    RightFoot, //13
    LeftHand, //14
    RightHand, //15
    LeftClav, //16
    RightClav, //17
    NoFlag, //18
    WeakPoint, //19
    None //20
};

enum Check {
    Chests, //0
    Heads, //1
    Necks, //2
    Arm, //3
    ForeArm, //4
    UpLeg, //5
    Leg, //6
    Foot //7
};





bool (*Ammo)(void* _this);
bool _Ammo(void* _this) {
    if (_this != NULL) {
        if (MazeTeam.aimkill) {
            return true;
        }
    }
    return Ammo(_this);
}



float (*Recoil)(void* _this);
float _Recoil(void* _this) {
    if (_this != NULL) {
     if (MazeTeam.aimkill) {
           return -15.0f;
    }
    return Recoil(_this);
}
}
    


void (*AimKill)(void *_this, int32_t pFireStatus, int32_t pFireMode);
void _AimKill(void *_this, int32_t pFireStatus, int32_t pFireMode) {
    if (_this != NULL) {
        if (MazeTeam.aimkill) {
            pFireStatus = FireStatus::FIRING;
            pFireMode = FireMode::AUTO;
        }
    }
    return AimKill(_this, pFireStatus, pFireMode);
}

bool (*Anim)(void* _this);
bool _Anim(void* _this) {
    if (_this != NULL) {
        if (MazeTeam.aimkill) {
            return true;
        }
	}
    return Anim(_this);
}


bool (*Camera)(void* _this, Quaternion Rotate);
bool _Camera(void* _this, Quaternion Rotate) {
    if (_this != NULL) {
        if (MazeTeam.aimkill) {
            return false;
        }
	}
    return Camera(_this, Rotate);
}

int (*IsAmmoFreehook)(void* player);
int _IsAmmoFreehook(void* player) {
    if (MazeTeam.aimkill) {
        return true;
    }
    return IsAmmoFreehook(player);
}

int (*Dano)(void* player);
int _Dano(void* player) {
    if (MazeTeam.aimkill) {
        return false;
    }
    return Dano(player);
}
//end



HOOK(0xBA9A18, _Dano, Dano);//public bool IsFiring() { }
HOOK(0x21218E4, _IsAmmoFreehook, IsAmmoFreehook);//1.70 public bool get_IsAmmoFree() { }
HOOK(0x2121B90, _Recoil, Recoil);//public float GetScatterRate() { }

HOOK(0x35C701C, _Camera, Camera);//public static Quaternion Euler(float x, float y, float z) { }
HOOK(0xDB19D0, _AimKill, AimKill); //public void KBNOKPOCLED(AKOPKPIDGEJ.OOCNCAKCHNO NPMEDEOKBID, AKOPKPIDGEJ.HHMOMGDFCCJ OCANOIDGCHL = 0) { }
HOOK(0x211798C, _Anim, Anim);//public void PlayFireAnim() { }
HOOK(0x177CC3C, _Anim, Anim);//public virtual void PlayFireAnim() { }
HOOK(0x13CFABC, _Ammo, Ammo);//public void SyncWeaponAmmoInClip(FHNKIFBANMH KMIPBIGPDPI) { }
//public void RecycleDamageNumObject(GameObject numObject) { }
TakeDamege = MemoryPatch::createWithHex("libil2cpp.so", 0xCCC430, "05 01 A0 E3 1E FF 2F E1");
//public bool IsShootingTarget() { }
TakeSkill = MemoryPatch("libil2cpp.so", 0x1635F9C, "\x00\x00\xA0\xE3\x1E\xFF\x2F\xE1", 8);//1.70




