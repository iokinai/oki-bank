#ifndef MODELS_USER_STATUS_HXX
#define MODELS_USER_STATUS_HXX

#include <cfg.hxx>

namespace okibank {

enum class SHARED_EXPORT user_status {
  offline,
  online,
  away,
};

}

#endif