#ifndef ASSETDIR_H
#define ASSETDIR_H

#if defined(PLATFORM_OSX)	

#define ASSET_DIR ""

#else

#define ASSET_DIR "../Assets"

#endif

#define SCENES_DIR ASSET_DIR "/Scenes"
#define SHADERS_DIR ASSET_DIR "/Shaders"
#define TEXTURES_DIR ASSET_DIR "/Textures"

#define TEXTURE_BILLBOARD_TEST TEXTURES_DIR "/BillboardTest.bmp"

#define SKYBOX_DIR TEXTURES_DIR "/Skybox"
#define SKYBOX_NIGHTSKY SKYBOX_DIR "/Nightsky"

#endif