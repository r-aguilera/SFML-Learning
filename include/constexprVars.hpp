#pragma once
#ifndef _CONSTEXPRVARS_
#define _CONSTEXPRVARS_

constexpr auto SpriteSpeed = 300;
constexpr auto WindowWidth = 1200;
constexpr auto WindowHeigth = 600;
constexpr auto FramesPerSecond = 60.f;
const auto TimePerFrame = sf::seconds(1.f / FramesPerSecond);

#endif // _CONSTEXPRVARS_
