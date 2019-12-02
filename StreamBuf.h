//
// Simple class to read/write data from/to buffer as it was a Stream
//
// (c)2017,2019 Alexander Emelianov (a.m.emelianov@gmail.com)
//

#pragma once

class StreamBuf : public Stream {
  public:
  StreamBuf(size_t len = 0) : Stream() {
    if (len) {
      buff = (uint8_t*)malloc(len);
      if (buff)
        length = len;
    }
  }
  StreamBuf(uint8_t* src, size_t len, bool filled = false) : Stream() {
    buff = src;
    length = len;
    if (filled)
      wpos = len - 1;
  }
  void reset() {
    return;
    rpos = 0;
    wpos = 0;
  }
  int read() {
    int t = peek();
    if (t >= 0)
      rpos++;
    return t;
  }
  int available() {
    if (rpos >= wpos) return 0;
    return wpos - rpos;
  }
  int peek() {
    if (rpos >= wpos) return -1;
    return buff[rpos];
  }
  size_t write(uint8_t b) {
    if (wpos >= length) {
      if (rpos == 0)
        return 0;
      memcpy(buff, buff+rpos, wpos - rpos);
      wpos -= rpos;
      rpos = 0;
    }
    buff[wpos] = b;
    wpos++;
    return 1;
  }
  void flush() {
    return;
  }
  private:
  size_t rpos = 0;
  size_t wpos = 0;
  uint8_t* buff = nullptr;
  size_t length = 0;
};

class DuplexBuf : public Stream {
public:
  DuplexBuf(Stream* rx, Stream* tx) {
    _rx = rx;
    _tx = tx;
  }
  /*
  void reset() {
    _rx->reset();
    _tx_>reset();
  }*/
  int read() {
    return _rx->read();
  }
  int available() {
    return _rx->available();
  }
  int peek() {
    return _rx->peek();
  }
  size_t write(uint8_t b) {
    return _tx->write(b);
  }
  void flush() {
    return;
  }
private:
  Stream* _rx;
  Stream* _tx;
};
