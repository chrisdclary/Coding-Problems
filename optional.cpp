/*
    A barebones version of the optional data type in c++
    If you want optionals but you are compiling in c++11
*/

template< class T >
class optional
{

  T content;
  bool hasValue = false;

  public:

    optional<T>& operator = ( T const &obj ) {
      content = obj;
      hasValue = true;
      return *this;
    }
    
    optional() = default;

    optional( T const &obj ) {
      content = obj;
      hasValue = true;
    }

    T value() {
      return content;
    }

    bool has_value() {
      return hasValue;
    }

    void reset() {
      hasValue = false;
    }
};