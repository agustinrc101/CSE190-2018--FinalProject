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

//Finishers (for textures) i.e TEXTURE_GROUND + TEXTURE_TYPE_ALBEDO_PNG
#define TEXTURE_TYPE_ALBEDO_TGA "Albedo.tga"
#define TEXTURE_TYPE_NORMAL_TGA "Normal.tga"
#define TEXTURE_TYPE_ALBEDO_PNG "Albedo.png"
#define TEXTURE_TYPE_NORMAL_PNG "Normal.png"
#define TEXTURE_TYPE_HEIGHT_PNG "Height.png"
#define TEXTURE_TYPE_METALLIC_PNG "Metallic.png"

//Textures
#define TEXTURE_GROUND "../assets/models/Environment/Ground/Textures/Ground_"
#define TEXTURE_ROCKS "../assets/models/Environment/Rocks/Textures/Rocks_"
#define TEXTURE_BUSH_TGA "../assets/models/Environment/Vegetation/Textures/BushBig_"
#define TEXTURE_PALMTREE_TGA "../assets/models/Environment/Vegetation/Textures/PalmTree/Palm_Tree_"
#define TEXTURE_HOUSE "../assets/models/Props/House/Textures/House_"
#define TEXTURE_AMMOBOX "../assets/models/Props/AmmoBox/Textures/AmmoBox_"
#define TEXTURE_BARREL "../assets/models/Props/Barrel//Textures/BlueBarrel_"
#define TEXTURE_BARRIER "../assets/models/Props/Barrier/Textures/Barrier_"
#define TEXTURE_CONTAINER_BLUE "../assets/models/Props/Container/Textures/BlueContainer_"
#define TEXTURE_CONTAINER_GREEN "../assets/models/Props/Container/Textures/GreenContainer_"
#define TEXTURE_CONTAINER_RED "../assets/models/Props/Container/Textures/RedContainer_"
#define TEXTURE_GRENADE "../assets/models/Props/Grenade/Textures/Grenade_"
#define TEXTURE_LADDER "../assets/models/Props/Ladders/Textures/Ladder_"
#define TEXTURE_TIRE "../assets/models/Props/Tires/Textures/TireWall_"
#define TEXTURE_CRATE1 "../assets/models/Props/Textures/WoodenCrate_"
#define TEXTURE_CRATE2 "../assets/models/Props/Textures/WoodenCrate2_"
#define TEXTURE_WEAPON_SHOTGUN "../assets/models/modern-weapons/870 Shotgun/Textures/870_Shotgun.fbx"
#define TEXTURE_WEAPON_AK47 "../assets/models/modern-weapons/AK-47/Textures/AK-47_.fbx"
#define TEXTURE_WEAPON_SNIPER "../assets/models/modern-weapons/L96 Sniper Rifle/Textures/L96_Sniper_Rifle_"
#define TEXTURE_WEAPON_M4 "../assets/models/modern-weapons/M4 Carbine/Textures/M4_Carbine_"
#define TEXTURE_WEAPON_PISTOL "../assets/models/modern-weapons/Pistol/Textures/Pistol_"
#define TEXTURE_WEAPON_SCIFI_HEAVY "../assets/models/scifi-weapons/Heavy/Textures/Shared/Heavy_"
#define TEXTURE_WEAPON_SCIFI_PISTOL "../assets/models/scifi-weapons/Pistol/Textures/Shared/Pistol.fbx"
#define TEXTURE_WEAPON_SCIFI_RIFLE "../assets/models/scifi-weapons/Rifle/Textures/Shared/Rifle.fbx"
#define TEXTURE_WEAPON_SCIFI_SNIPER "../assets/models/scifi-weapons/Sniper/Textures/Shared/Sniper.fbx"
#define TEXTURE_CAN_JPG "../assets/models/Props/Can/Matcha_Can_Albedo.jpg"
#define TEXTURE_MATTHEW_PNG "../assets/models/Matthew/model_0.png"
#define TEXTURE_CUBE_PPM "../assets/textures/pattern.ppm"

//Models
#define MODEL_ROCKS "../assets/models/Environment/Rocks/Rocks.fbx"
#define MODEL_PALMTREE1 "../assets/models/Environment/Vegetation/PalmTree.fbx"
#define MODEL_PALMTREE2 "../assets/models/Environment/Vegetation/PalmTree2.fbx"
#define MODEL_BUSH "../assets/models/Environment/Vegetation/BushBig.fbx"
#define MODEL_HOUSE1 "../assets/models/Props/House/House.fbx"
#define MODEL_HOUSE2 "../assets/models/Props/House/House2.fbx"
#define MODEL_AMMOBOX "../assets/models/Props/AmmoBox/AmmoBox.fbx"
#define MODEL_BARREL "../assets/models/Props/Barrel/Barrel.fbx"
#define MODEL_BARRIER "../assets/models/Props/Barrier/ConcreteBarrier.fbx"
#define MODEL_CONTAINER "../assets/models/Props/Container/Container.fbx"
#define MODEL_GRENADE	"../assets/models/Props/Grenade/Grenade.fbx"
#define MODEL_LADDER_SMALL "../assets/models/Props/Ladders/SmallLadder.fbx"
#define MODEL_LADDER_TALL "../assets/models/Props/Ladders/TallLadder.fbx"
#define MODEL_TIRE "../assets/models/Props/Tires/SingleTire.fbx"
#define MODEL_TIRE_WALL "../assets/models/Props/Tires/TireWall.fbx"
#define MODEL_CRATE "../assets/models/Props/WoodenCrate/WoodenCrate.fbx"
#define MODEL_WEAPON_SHOTGUN "../assets/models/modern-weapons/870 Shotgun/870_Shotgun.fbx"
#define MODEL_WEAPON_AK47 "../assets/models/modern-weapons/AK-47/AK-47.fbx"
#define MODEL_WEAPON_SNIPER "../assets/models/modern-weapons/L96 Sniper Rifle/L96_Sniper_Rifle.fbx"
#define MODEL_WEAPON_M4 "../assets/models/modern-weapons/M4 Carbine/M4_Carbine.fbx"
#define MODEL_WEAPON_PISTOL "../assets/models/modern-weapons/Pistol/Pistol.fbx"
#define MODEL_WEAPON_SCIFI_HEAVY "../assets/models/scifi-weapons/Heavy/Heavy.fbx"
#define MODEL_WEAPON_SCIFI_PISTOL "../assets/models/scifi-weapons/Pistol/Pistol.fbx"
#define MODEL_WEAPON_SCIFI_RIFLE "../assets/models/scifi-weapons/Rifle/Rifle.fbx"
#define MODEL_WEAPON_SCIFI_SNIPER "../assets/models/scifi-weapons/Sniper/Sniper.fbx"
#define MODEL_CAN "../assets/models/Props/Can/Matcha_Can.obj"
#define MODEL_MATTHEW "../assets/models/Matthew/model_0.obj"
#define MODEL_SHAPE_SPHERE "../assets/models/sphere.obj"
#define MODEL_SHAPE_CUBE "../assets/models/cube.obj"
#define MODEL_SHAPE_PLANE "../assets/models/plane.fbx"

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

#endif //FILEPATHSANDDEFINITIONS_H