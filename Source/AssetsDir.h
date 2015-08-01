#ifndef ASSETDIR_H
#define ASSETDIR_H

#if defined(PLATFORM_OSX)	

#define ASSET_DIR ""

#else

#define ASSET_DIR "../Assets"

#endif

#define MODEL_DIR "/Models"

#define SCENES_DIR ASSET_DIR "/Scenes"
#define SHADERS_DIR ASSET_DIR "/Shaders"
#define TEXTURES_DIR ASSET_DIR "/Textures"

#define TEXTURE_BILLBOARD_TEST TEXTURES_DIR "/BillboardTest.bmp"

#define SKYBOX_DIR TEXTURES_DIR "/Skybox"
#define SKYBOX_NIGHTSKY SKYBOX_DIR "/Nightsky"

#define SHEEP_DIR "/Sheep"
#define HOLY_SHEEP ASSET_DIR MODEL_DIR SHEEP_DIR "/SHEEP.obj"
#define HOLY_SHEEP_MATERIAL ASSET_DIR MODEL_DIR SHEEP_DIR "/"

#define WOLF_DIR "/Wolf"
#define HOLY_WOLF ASSET_DIR MODEL_DIR WOLF_DIR "/Wolf.obj"
#define HOLY_WOLF_MATERIAL ASSET_DIR MODEL_DIR WOLF_DIR "/"
#endif