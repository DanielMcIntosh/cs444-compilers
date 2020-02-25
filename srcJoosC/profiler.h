#pragma once

struct ProfileScopeImpl;

ProfileScopeImpl* profileSectionFunc(const char* file,
                                     int line,
                                     const char* name);
void profileSectionEndFunc(ProfileScopeImpl*);

struct ProfileScope {
  ProfileScopeImpl* impl;
  ProfileScope(const char* file_, int line_, const char* name_) ;
  ~ProfileScope();
};

#define CONCAT(_x, _y) _x##_y
#define CONCAT2(_x, _y) CONCAT(_x, _y)

//#define profileSection(_name)
//  ProfileScope CONCAT2(_profileScope_, __COUNTER__)(__FILE__, __LINE__, _name)

#define profileSection(_name)

void profileReport();
