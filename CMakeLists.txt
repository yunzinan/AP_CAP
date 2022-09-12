cmake_minimum_required(VERSION 3.21)
project(CAP)

set(CMAKE_CXX_STANDARD 14)

add_executable(CAP main.cpp LoginScene.cpp LoginScene.h AccountCenter.cpp AccountCenter.h BuyerCenter.cpp BuyerCenter.h SellerCenter.cpp SellerCenter.h AuctionSystem.cpp AuctionSystem.h MyNode.h)
