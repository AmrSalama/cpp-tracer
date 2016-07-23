#ifndef INCLUDE_TRACER_IMPL_ARRAY_H_
#define INCLUDE_TRACER_IMPL_ARRAY_H_

#include <string>
#include "GL/gl.h"
#include "GL/freeglut.h"
#include "tracer/core/color.h"
#include "tracer/core/utility/gl.h"

namespace tracer {

template<typename T>
int ArrayTracer<T>::render_index = -1;

template<typename T>
ArrayTracer<T>::ArrayTracer(T* array,
                            size_t size,
                            float speed,
                            std::string window_title)
    : kRectangleWidth(50.0), kRectangleHeight(50.0), kWindowPadding(15.0),
      Tracer(0,
             NULL,
             (size * 50.0) + (15.0 * 2),  // 50 for rect width, 15 for padding
             50.0 + (15.0 * 2),           // 50 for rect height, 15 for padding
             speed,
             window_title) {
  size_ = size;
  array_.resize(size);
  colors_.assign(size, core::Color(100, 200, 200));
  for (int i = 0; i < size; i++)
    array_[i] = array[i];

  flush(0.2);
}

template<typename T>
ArrayTracer<T>::~ArrayTracer() {}

template<typename T>
void ArrayTracer<T>::render() {
  float beginning_x = kWindowPadding;
  if (render_index < 0) {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < size_; i++) {
        core::utility::gl::draw_rectangle((beginning_x + i*kRectangleWidth),
                                    (window_height_/2.0 - kRectangleHeight/2.0),
                                    kRectangleWidth,
                                    kRectangleHeight,
                                    array_[i],
                                    colors_[i]);
    }
  } else {
    core::utility::gl::draw_rectangle((beginning_x + render_index*kRectangleWidth),
                                (window_height_/2.0 - kRectangleHeight/2.0),
                                kRectangleWidth,
                                kRectangleHeight,
                                array_[render_index],
                                colors_[render_index]);
  }

  glFlush();
}

template<typename T>
void ArrayTracer<T>::notify(size_t index, float speed) {
  speed = (speed > 0 ? speed : speed_);

  render_index = index;
  colors_[index].set_red(255);
  flush(speed);
  colors_[index].set_red(100);
  flush(speed);
  render_index = -1;
}

template<typename T>
void ArrayTracer<T>::select(size_t index, float speed) {
  speed = (speed > 0 ? speed : speed_);

  render_index = index;
  colors_[index].set_blue(255);
  flush(speed);
  render_index = -1;
}

template<typename T>
void ArrayTracer<T>::deselect(size_t index, float speed) {
  speed = (speed > 0 ? speed : speed_);

  render_index = index;
  colors_[index].set_blue(200);
  flush(speed);
  render_index = -1;
}

}  // namespace tracer

#endif  // INCLUDE_TRACER_IMPL_ARRAY_H_
