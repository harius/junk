/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ServiceDefinition_TYPES_H
#define ServiceDefinition_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>



namespace junk
{

typedef struct _Vector2f__isset
{

  _Vector2f__isset() : x(false), y(false)
  {
  }
  bool x;
  bool y;
} _Vector2f__isset;

class Vector2f
{
public:

  static const char* ascii_fingerprint; // = "EA2086D2BB14222991D7B0497DE7B58B";
  static const uint8_t binary_fingerprint[16]; // = {0xEA,0x20,0x86,0xD2,0xBB,0x14,0x22,0x29,0x91,0xD7,0xB0,0x49,0x7D,0xE7,0xB5,0x8B};

  Vector2f() : x(0), y(0)
  {
  }

  virtual ~Vector2f() throw ()
  {
  }

  double x;
  double y;

  _Vector2f__isset __isset;

  void __set_x(const double val)
  {
    x = val;
  }

  void __set_y(const double val)
  {
    y = val;
  }

  bool operator ==(const Vector2f & rhs) const
  {
    if (!(x == rhs.x))
      return false;
    if (!(y == rhs.y))
      return false;
    return true;
  }

  bool operator !=(const Vector2f &rhs) const
  {
    return !(*this == rhs);
  }

  bool operator<(const Vector2f &) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(Vector2f &a, Vector2f &b);

} // namespace

#endif
