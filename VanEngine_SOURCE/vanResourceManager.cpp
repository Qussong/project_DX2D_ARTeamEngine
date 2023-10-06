#include "vanResourceManager.h"

namespace van
{
	std::map<std::wstring, Resource*> ResourceManager::mResourceManager;

	void ResourceManager::Release()
	{
		std::map<std::wstring, Resource*>::iterator iter = mResourceManager.begin();
		for (; iter != mResourceManager.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
}
