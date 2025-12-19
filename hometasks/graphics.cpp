#include <string>
#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include "GUI.h"
#include "Graph.h"
#include "Window.h"
#include "vec2d.h"
#include "poly.h"
#include "Simple_window.h"
#include <FL/Fl.H> 


using namespace Graph_lib;

void dragon_fractal_step(std::list<Vec2d>& curve)
{
    auto prev = curve.begin();
    auto curr = std::next(prev);
    bool sign = true;  // чередуем направление

    while (curr != curve.end())
    {
        Vec2d v = *curr - *prev;
        Vec2d mid = *prev + v * 0.5;     // середина сегмента
        Vec2d rotated_half = rotated(sign ? pi/2 : -pi/2, mid + v*0.5, mid) - mid;
        Vec2d m = mid + rotated_half;          // вставляем новую точку

        curve.insert(curr, m);        // вставляем сегмент

        prev = curr;  //обновляем
        ++curr;

        sign = !sign;      // чередуем
    }
}



auto max_edge_length (const std::list<Vec2d>& curve)
{

  double d = 0.;
  auto prev = --curve.end();
  for (auto curr = curve.begin(); curr != curve.end(); ++curr, ++prev)
  {
    d = std::max(d, length(*curr - *prev));
    prev = curr;
  }

  return d;
}

void draw_dragon (int w, int n)
{
  Simple_window win{Point{100, 100}, w, w, "Dragon"};

  Vec2d c{w / 2., w / 2.};  
  double r{0.85 * w / 2.};  // для первого сегмента

  std::list<Vec2d> ngon;              // первый сегмент
  ngon.push_back(c + Vec2d{-r, 0});   // левый конец
  ngon.push_back(c + Vec2d{ r, 0});   // правый конец

  Text n_steps{as_point(c), "0"};
  n_steps.set_color(Color::blue);
  win.attach(n_steps);

  for (bool is_fine = false; !is_fine;)
  {
    Open_polyline curve;
    for (const auto& v : ngon) {
    curve.add(Point{static_cast<int>(std::lround(v.x)),  //рисуем все ьточки из ngon 
                    static_cast<int>(std::lround(v.y))});
    }

    curve.set_color(Color::blue);

    win.attach(curve);
    win.redraw();  

    //Fl::wait(0.5); 
    win.wait_for_button();
    
    dragon_fractal_step(ngon);

    is_fine = max_edge_length(ngon) < 1.0; //дойти до мелких сегментов
    if (is_fine)
      n_steps.set_color(Color::red);

    win.detach(curve);
    n_steps.set_label(std::to_string(std::stoi(n_steps.label()) + 1));
  }
}

void help (const char prog[])
{
  std::cerr << "Generate Koch fractal on a regular polygon\n\n"
               "Usage: "
            << prog
            << " [-h|--help] [window width] [ignored]\n"
            << std::endl;
}

int main (int argc, char* argv[])
try
{
  int w = 410;  // window width
  int n = 3;  

  draw_dragon(w, n);
}
catch (std::invalid_argument& e)
{
  // check if user asks help
  for (int i = 1; i < argc; ++i)
  {
    std::string arg{argv[i]};
    if (arg == "-h" || arg == "--help")
    {
      help(argv[0]);
      return 2;
    }
  }

  // else expected an integer
  std::cerr << e.what() << ": not an integer\n" << std::endl;
  return 2;
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}
