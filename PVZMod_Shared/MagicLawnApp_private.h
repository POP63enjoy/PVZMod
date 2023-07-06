#pragma once

namespace PVZMod::__MAGIC_LAWNAPP_PRIVATE__
{
	extern std::function<SexyString(LawnApp* _this, GameMode theLevelId, const std::function<SexyString()>& defaultNameFunc)> GetAppLevelName;
}