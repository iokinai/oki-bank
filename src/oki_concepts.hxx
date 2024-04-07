#ifndef OKI_CONCEPTS_HXX
#define OKI_CONCEPTS_HXX

template <class T>
concept is_http_server = requires(T t) {
  { t.Get() };
  { t.Post() };
};

#endif