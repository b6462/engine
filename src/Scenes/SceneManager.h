#pragma once

#include "../defines.h"
#include "../Helpers/TimerManager.h"
#include "../Helpers/Stopwatch.h"
#include "../Helpers/Singleton.h"
#include <memory>
#include <map>
#include <vector>

#ifdef ANDROID
#include <android_native_app_glue.h>
#endif

namespace star
{
	struct Context;
	class BaseScene;
	class UIBaseCursor;
	class Object;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		friend Singleton<SceneManager>;

		BaseScene* GetActiveScene();
		BaseScene* GetScene(const tstring & name);
		template <typename T>
		T* GetScene(const tstring & name);
		bool SetActiveScene(const tstring & name);
		bool AddScene(BaseScene* scene);
		bool AddScene(const tstring & name, BaseScene* scene);
		bool RemoveScene(const tstring & name);

		void Update(const Context& context);
		void Draw();

		void DrawDefaultCursor();
		void UpdateDefaultCursor(const Context & context);

		void SetDefaultCursor(UIBaseCursor * cursor);
		void UnsetDefaultCursor();

		void SetDefaultCursorState(const tstring & state);
		void SetDefaultCursorLocked(bool locked);
		bool IsDefaultCursorLocked() const;
		bool IsDefaultCursorDefined() const;

		void SetSystemCursorHiddenByDefault(bool hidden);

		std::shared_ptr<TimerManager> GetTimerManager() const;

#ifdef ANDROID
		void processActivityEvent(int32 pCommand, android_app* pApplication);
		int32 processInputEvent(AInputEvent* pEvent);

	private:
		android_app* mApplicationPtr;
#endif
	private:
		BaseScene	*m_ActiveScene, 
					*m_NewActiveScene;

		std::shared_ptr<TimerManager> m_TimerManager;

		std::vector<BaseScene*> m_GarbageList;
		std::map<tstring, BaseScene*> m_SceneList;
		bool m_bSwitchingScene,
			 m_bInitialized,
			 m_bDestroyRequested,
			 m_bCursorHiddenByDefault,
			 m_bCustomCursorDefined;
		tstring m_CurrentSceneName;
		UIBaseCursor *m_pDefaultCursor;

		bool InitializeCurScene(const Context& context);

		SceneManager();
		~SceneManager();

		void CreateDefaultCursor();

		SceneManager(const SceneManager& yRef);
		SceneManager(SceneManager&& yRef);
		SceneManager& operator=(const SceneManager& yRef);
		SceneManager& operator=(SceneManager&& yRef);
	};
}

#include "SceneManager.inl"
