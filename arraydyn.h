/*------------------------------------------------------------------------------
  A R R A Y D Y N . H

  Ein Klassen-Template für ein mehrdimensionales dynamisches Array.
  Lediglich der Typ des Arrays und die Anzahl der Dimensionen müssen zur
  Compile-Zeit festgelegt werden.

  Durch die Verwendung von Proxy-Klassen können die Arrays genau wie statische
  Arrays angesprochen werden.

  Beipiel: ArrayDyn<int,3> wuerfel(8,8,8);
           wuerfel[1][2][3] = 4;
------------------------------------------------------------------------------*/
#pragma once

//------------------------------------------------------------------------------
template <typename T, size_t N>
class ArrayDynProxy {
//------------------------------------------------------------------------------
  friend class ArrayDynProxy<T, N + 1>;
public:
  ArrayDynProxy<T, N - 1> operator [] (size_t i) {
    return ArrayDynProxy<T, N - 1>(sizes + 1, data + *sizes * i);
  }
  operator T*() { return data; }
protected:
  template <typename... D2N>
  ArrayDynProxy(size_t d1, D2N... d2n) {
    set(sizeof(T), d1, d2n...);
    data = (T*) (sizes + N - 1);
  }
  void destruct() { free(sizes); }
private:
  ArrayDynProxy(size_t* sizes, T* data) : sizes(sizes), data(data) {}
  template<typename...D2N>
  size_t set(size_t size, size_t d1, D2N... d2n) {
    // GCC doesn't like to have this call inside the return!
    size_t s = set(size * d1, d2n...);
    return d1 * (sizes[N - 1 - sizeof...(d2n)] = s);
  }
  size_t set(size_t size, size_t dn) {
    sizes = (size_t*) malloc(sizeof(size_t) * (N - 1) + size * dn);
    if (sizes == 0) { throw 0; }
    return dn;
  }
  size_t* sizes;
  T*      data;
};

//------------------------------------------------------------------------------
template <typename T>
class ArrayDynProxy<T, 1> {
//------------------------------------------------------------------------------
  friend class ArrayDynProxy<T, 2>;
public:
  T& operator [] (size_t i) { return data[i]; }
  operator T*() { return data; }
protected:
  ArrayDynProxy(size_t d1) {
    data = (T*) malloc(sizeof(T) * d1);
    if (data == 0) { throw 0; }
  }
  void destruct() { free(data); }
private:
  ArrayDynProxy(size_t*, T* data) : data(data) {}
  T* data;
};

//------------------------------------------------------------------------------
template <typename T, size_t N>
class ArrayDyn : public ArrayDynProxy<T, N> {
//------------------------------------------------------------------------------
public:
  template <typename... D2N>
  ArrayDyn(size_t d1, D2N... d2n) : ArrayDynProxy<T, 1 + sizeof...(D2N)>(d1, d2n...) { }
  ~ArrayDyn() { this->destruct(); }
};
