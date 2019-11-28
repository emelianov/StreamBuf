//
// Simple class to read data from buffer as it was Stream
//
// (c)2017, Alexander Emelianov (a.m.emelianov@gmail.com)
//

#pragma once

class StreamBuf : public Stream {
  public:
  StreamBuf() : Stream() {
    buff = NULL;
    length = 0;
    pos = 0;
  }
  StreamBuf(uint8_t* src, size_t len) : Stream() {
    buff = src;
    length = len;
    pos = 0;
  }
  void open(uint8_t* src, size_t len) {
    buff = src;
    length = len;
    pos = 0;
    //Serial.println(len);    
  }
  void reset() {
    pos = 0;
  }
  int read() {
    if (pos >= length) return -1;
    uint8_t t = buff[pos];
    pos++;
    return t;
  }
  int available() {
    if (pos >= length) return -1;
    return length - pos;
  }
  int peek() {
    return -1;
  }
  size_t write(uint8_t b) {
    return -1;
  }
  void flush() {
    pos = length;
  }
  private:
  size_t pos;
  uint8_t* buff;
  size_t length;
};
