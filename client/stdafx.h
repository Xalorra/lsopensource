
#pragma once

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable : 4715)

#define __EX __declspec(dllimport)

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE


#include "../io3DEngine/ioPrerequisites.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <dsound.h>
#include <tchar.h>
#include <strsafe.h>
#include <atlbase.h>	
#include <atlcom.h>		
#include <atlhost.h>
#include <GdiPlus.h>
#include <Wininet.h>
#include <atltime.h>
#include "typeinfo.h"


#include "../LSLog/include/LSLog.h"

#include "../io3DEngine/io3DCommon.h"
#include "../io3DEngine/ioVertexFormat.h"
#include "../io3DEngine/ioFrameTimer.h"
#include "../io3DEngine/ioTimer.h"

#include "../TownPortal/include/TownPortal.h"

#pragma comment(lib, "../../lib/LSLog.lib" )
#pragma comment(lib, "../../lib/io3DEngine.Lib")
#pragma comment(lib, "../../lib/TownPortal.lib")
#pragma comment(lib, "../../lib/CrashFind.lib")
#pragma comment(lib, "../../lib/ioPac.lib" )
#pragma comment(lib, "gdiplus" )

#include "VeryOftenUseDefine.h"

#define USE_LIST_ARQUMENTS_TEXT_FUNCTION // 해외버전은 가변인자 사용하면 안되므로 주석 처리해서 테스트



//io3DEngine
#include "../io3DEngine/ioGUIManager.h"
#include "../io3DEngine/ioUIFrameManager.h"
#include "../io3DEngine/ioWnd.h"
#include "../io3DEngine/ioButton.h"
#include "../io3DEngine/ioScroll.h"
#include "../io3DEngine/ioFontManager.h"
#include "../io3DEngine/ioINILoader.h"
#include "../io3DEngine/ioEffect.h"
#include "../io3DEngine/HelpFunc.h"
#include "../io3DEngine/ioEntityGroup.h"
#include "../io3DEngine/ioStringConverter.h"
#include "../io3DEngine/ioUIRenderImage.h"
#include "../io3DEngine/ioUIRenderFrame.h"
#include "../io3DEngine/ioUITitle.h"
#include "../io3DEngine/Safesprintf.h"
#include "../io3DEngine/ioUIImageSetManager.h"
#include "../io3DEngine/ioCPU.h"
#include "../io3DEngine/ioRenderSystem.h"
#include "../io3DEngine/ioCamera.h"
#include "../io3DEngine/ioCameraController.h"
#include "../io3DEngine/ioLookAtCameraController.h"
#include "../io3DEngine/ioResourceManager.h"
#include "../io3DEngine/ioTexture.h"
#include "../io3DEngine/ioTextureManager.h"
#include "../io3DEngine/ioMeshManager.h"
#include "../io3DEngine/ioMaterialManager.h"
#include "../io3DEngine/ioSkeletonManager.h"
#include "../io3DEngine/ioAnimationManager.h"
#include "../io3DEngine/ioAnimationEventManager.h"
#include "../io3DEngine/ioShaderManager.h"
#include "../io3DEngine/ioSoundManager.h"
#include "../io3DEngine/ioTextureEffectManager.h"
#include "../io3DEngine/ioEffectFactory.h"
#include "../io3DEngine/ioVertexBufferManager.h"
#include "../io3DEngine/ioIndexBufferManager.h"
#include "../io3DEngine/ioOpcodeManager.h"
#include "../io3DEngine/ioAnimateFXManager.h"
#include "../io3DEngine/ioMeshTrailDataManager.h"
#include "../io3DEngine/ioUIRenderer.h"
#include "../io3DEngine/ioSceneManager.h"
#include "../io3DEngine/ioEntityGroupBuilder.h"
#include "../io3DEngine/InputBox.h"
#include "../io3DEngine/ioMeshTrailer.h"
#include "../io3DEngine/ioEdit.h"
#include "../io3DEngine/ioStream.h"
#include "../io3DEngine/ioResourceLoader.h"
#include "../io3DEngine/ErrorReport.h"
#include "../io3DEngine/ioThreadTaskManager.h"
#include "../io3DEngine/iostringmanager.h"
#include "../io3DEngine/ioMath.h"
#include "../io3DEngine/ioRenderQueue.h"
#include "../io3DEngine/ioOrientBox.h"
#include "../io3DEngine/ioSegMent.h"
#include "../io3DEngine/ioNode.h"
#include "../io3DEngine/ioEntity.h"
#include "../io3DEngine/ioSubEntity.h"
#include "../io3DEngine/ioTechnique.h"
#include "../io3DEngine/ioMaterial.h"
#include "../io3DEngine/ioPass.h"
#include "../io3DEngine/ioTextureUnitState.h"
#include "../io3DEngine/ioStringInterface.h"
#include "../io3DEngine/ioSceneNode.h"
#include "../io3DEngine/ioSkyDome.h"
#include "../io3DEngine/ioOpcodeShape.h"
#include "../io3DEngine/ioParticleSystem.h"
#include "../io3DEngine/ioUI3DEffectRender.h"
#include "../io3DEngine/ioRay.h"
#include "../io3DEngine/ioRenderable.h"
#include "../io3DEngine/ioMovableObject.h"
#include "../io3DEngine/ioMesh.h"
#include "../io3DEngine/ioAnimation.h"
#include "../io3DEngine/ioBiped.h"
#include "../io3DEngine/ioSkeleton.h"
#include "../io3DEngine/ioCylinder.h"
#include "../io3DEngine/ioXMLDocument.h"
#include "../io3DEngine/ioXMLElement.h"
#include "../io3DEngine/ioINIParser.h"
#include "../io3DEngine/ioMovingWnd.h"
#include "../io3DEngine/ioUITitle.h"
