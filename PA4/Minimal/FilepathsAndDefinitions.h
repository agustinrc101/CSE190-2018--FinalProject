#pragma once

#ifndef FILEPATHSANDDEFINITIONS_H
#define FILEPATHSANDDEFINITIONS_H

//Shader paths
#define SHADER_COLOR_VERT_PATH "../assets/shaders/ColorShader.vert"
#define SHADER_COLOR_FRAG_PATH "../assets/shaders/ColorShader.frag"
#define SHADER_TEX_VERT_PATH "../assets/shaders/TextureShader.vert"
#define SHADER_TEX_FRAG_PATH "../assets/shaders/TextureShader.frag"
#define SHADER_SKY_VERT_PATH "../assets/shaders/SkyboxShader.vert"
#define SHADER_SKY_FRAG_PATH "../assets/shaders/SkyboxShader.frag"
#define SHADER_TEXTURE_VERT_PATH "../assest/shaders/shader.vert"
#define SHADER_TEXTURE_FRAG_PATH "../assest/shaders/shader.frag"

//Calibration cube path
#define CUBE_TEX_PATH "../assets/textures/pattern.ppm"
#define SKY_TEX_PATH "../assets/textures/sky/"

//Basic paths
#define MODEL_PATH "../assets/models/"
#define AUDIO_FX_PATH "../assets/audio/FX/"
#define TEXTURE_PATH "../assets/textures/"

//Textures
#define TEXTURE_GROUND1 "../assets/models/Environment/Ground/Textures/Ground_Albedo.ppm"
#define TEXTURE_GROUND2 "../assets/textures/floor/Sand/Sand_Albedo.ppm"
#define TEXTURE_ROCKS "../assets/models/Environment/Rocks/Textures/Rocks_Albedo.ppm"
//#define TEXTURE_BUSH "../assets/models/Environment/Vegetation/Textures/BushBig_Albedo.ppm"
//#define TEXTURE_PALMTREE "../assets/models/Environment/Vegetation/Textures/PalmTree/Palm_Tree_Albedo.ppm"
#define TEXTURE_HOUSE "../assets/models/Props/House/Textures/House_Albedo.ppm"
#define TEXTURE_AMMOBOX "../assets/models/Props/AmmoBox/Textures/AmmoBox_Albedo.ppm"
#define TEXTURE_BARREL "../assets/models/Props/Barrel//Textures/BlueBarrel_Albedo.ppm"
#define TEXTURE_BARRIER "../assets/models/Props/Barrier/Textures/Barrier_Albedo.ppm"
#define TEXTURE_CONTAINER_BLUE "../assets/models/Props/Container/Textures/BlueContainer_Albedo.ppm"
#define TEXTURE_CONTAINER_GREEN "../assets/models/Props/Container/Textures/GreenContainer_Albedo.ppm"
#define TEXTURE_CONTAINER_RED "../assets/models/Props/Container/Textures/RedContainer_Albedo.ppm"
#define TEXTURE_GRENADE "../assets/models/Props/Grenade/Textures/Grenade_Albedo.ppm"
#define TEXTURE_LADDER "../assets/models/Props/Ladders/Textures/Ladder_Albedo.ppm"
//#define TEXTURE_TIRE "../assets/models/Props/Tires/Textures/TireWall_Albedo.ppm"
#define TEXTURE_CRATE1 "../assets/models/Props/Textures/WoodenCrate_Albedo.ppm"
#define TEXTURE_CRATE2 "../assets/models/Props/Textures/WoodenCrate2_Albedo.ppm"
#define TEXTURE_WEAPON_SHOTGUN "../assets/models/modern-weapons/870 Shotgun/Textures/870_Shotgun_Albedo.ppm"
#define TEXTURE_WEAPON_AK47 "../assets/models/modern-weapons/AK-47/Textures/AK-47_Albedo.ppm"
#define TEXTURE_WEAPON_SNIPER "../assets/models/modern-weapons/L96 Sniper Rifle/Textures/L96_Sniper_Rifle_Albedo.ppm"
#define TEXTURE_WEAPON_M4 "../assets/models/modern-weapons/M4 Carbine/Textures/M4_Albedo.ppm"
#define TEXTURE_WEAPON_PISTOL "../assets/models/modern-weapons/Pistol/Textures/Pistol_Albedo.ppm"
#define TEXTURE_WEAPON_SCIFI_HEAVY "../assets/models/scifi-weapons/Heavy/Textures/Variation 08/Heavy_08_Albedo.ppm"
#define TEXTURE_WEAPON_SCIFI_PISTOL "../assets/models/scifi-weapons/Pistol/Textures/Variation 01/Pistol_01_Albedo.ppm"
#define TEXTURE_WEAPON_SCIFI_RIFLE "../assets/models/scifi-weapons/Rifle/Textures/Variation 06/Rifle_06_Albedo.ppm"
#define TEXTURE_WEAPON_SCIFI_SNIPER "../assets/models/scifi-weapons/Sniper/Textures/Variation 04/Sniper_04_Albedo.ppm"
#define TEXTURE_CAN "../assets/models/Props/Can/Matcha_Can_Albedo.ppm"
#define TEXTURE_MATTHEW "../assets/models/Matthew/model_0.ppm"
#define TEXTURE_CUBE "../assets/textures/pattern.ppm"
#define TEXTURE_MASK "../assets/models/Mask/Mask_head.ppm"

//Models
#define MODEL_ROCKS "../assets/models/Environment/Rocks/Rocks.fbx"
//#define MODEL_PALMTREE1 "../assets/models/Environment/Vegetation/PalmTree.fbx"
//#define MODEL_PALMTREE2 "../assets/models/Environment/Vegetation/PalmTree2.fbx"
//#define MODEL_BUSH "../assets/models/Environment/Vegetation/BushBig.fbx"
#define MODEL_HOUSE1 "../assets/models/Props/House/House.fbx"
//#define MODEL_HOUSE2 "../assets/models/Props/House/House2.fbx"
#define MODEL_AMMOBOX "../assets/models/Props/AmmoBox/AmmoBox.fbx"
#define MODEL_BARREL "../assets/models/Props/Barrel/Barrel-1.fbx"
#define MODEL_BARRIER "../assets/models/Props/Barrier/ConcreteBarrier.fbx"
#define MODEL_CONTAINER "../assets/models/Props/Container/Container-1.fbx"
#define MODEL_GRENADE	"../assets/models/Props/Grenade/Grenade.fbx"
#define MODEL_LADDER_SMALL "../assets/models/Props/Ladders/SmallLadder.fbx"
#define MODEL_LADDER_TALL "../assets/models/Props/Ladders/TallLadder.fbx"
//#define MODEL_TIRE "../assets/models/Props/Tires/SingleTire.fbx"
//#define MODEL_TIRE_WALL "../assets/models/Props/Tires/TireWall.fbx"
#define MODEL_CRATE "../assets/models/Props/WoodenCrate/WoodenCrate.fbx"
#define MODEL_WEAPON_SHOTGUN "../assets/models/modern-weapons/870 Shotgun/870_Shotgun.fbx"
#define MODEL_WEAPON_AK47 "../assets/models/modern-weapons/AK-47/AK-47.fbx"
#define MODEL_WEAPON_SNIPER "../assets/models/modern-weapons/L96 Sniper Rifle/L96_Sniper_Rifle.fbx"
#define MODEL_WEAPON_M4 "../assets/models/modern-weapons/M4 Carbine/M4_Carbine.fbx"
#define MODEL_WEAPON_PISTOL "../assets/models/modern-weapons/Pistol/Pistol.fbx"
#define MODEL_WEAPON_SCIFI_HEAVY "../assets/models/scifi-weapons/Heavy/Heavy.fbx"
#define MODEL_WEAPON_SCIFI_PISTOL "../assets/models/scifi-weapons/Pistol/Pistol-2.fbx"
#define MODEL_WEAPON_SCIFI_RIFLE "../assets/models/scifi-weapons/Rifle/Rifle.fbx"
#define MODEL_WEAPON_SCIFI_SNIPER "../assets/models/scifi-weapons/Sniper/Sniper.fbx"
#define MODEL_CAN "../assets/models/Props/Can/Matcha_Can.fbx"
#define MODEL_MATTHEW "../assets/models/Matthew/model_0.obj"
#define MODEL_SHAPE_SPHERE "../assets/models/sphere.obj"
#define MODEL_SHAPE_CUBE "../assets/models/cube.obj"
#define MODEL_SHAPE_PLANE "../assets/models/plane.fbx"
#define MODEL_MASK "../assets/models/Mask/Mask_head.fbx"

//Sounds
#define SOUND_MUSIC_SWEETWATER "../assets/audio/Music/Sweetwater.wav"
#define SOUND_MUSIC_DESERTCITY "../assets/audio/Music/Desert_City.wav"
#define SOUND_FX_BULLET_CASING "../assets/audio/FX/bullet_casing.wav"
#define SOUND_FX_BULLET_FLYBY "../assets/audio/FX/bullet_flyby.wav"
#define SOUND_FX_BULLET_IMPACT "../assets/audio/FX/bullet_impact.wav"
#define SOUND_FX_BULLET_SHELL_BOUNCE "../assets/audio/FX/bullet_shell_bounce_wood.wav"
#define SOUND_FX_PLAYER_HURT "../assets/audio/FX/classic_hurt.wav"
#define SOUND_FX_EXPLOSION "../assets/audio/FX/explosion.wav"
#define SOUND_FX_GUN_SUBMACHINE "../assets/audio/FX/gun_submachine.wav"
#define SOUND_FX_GUNSHOT "../assets/audio/FX/gunshot.wav"
#define SOUND_FX_GUNSHOT_SILENCED "../assets/audio/FX/silence_gunshot.wav"

//Definitions
#define PI 3.14159265359f
#define MINPRESS 0.7f //Defines the minimum press strength required for the triggers
#define COOLDOWN 0.2f

#endif //FILEPATHSANDDEFINITIONS_H