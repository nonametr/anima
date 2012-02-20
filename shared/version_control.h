#ifndef VERSION_CONTROL_H
#define VERSION_CONTROL_H

#include "config.h"

#define VCS_GIT "GIT"
#define MAJOR_VERSION "0.1."
class VCBase
{
public:
    virtual string getVersion();
protected:
    string _full_version;
    string _major_version;
    string _minor_version;
    string _build_version;
};
class GitVC : public VCBase
{
public:
    GitVC();
    string getVersion();
};
class VersionControl : public Singleton<VersionControl>
{
public:
    VersionControl();
    ~VersionControl(){ if(vc) delete vc; };
    string getVersion();
private:
    VCBase *vc;
    string _vcs_name;
};

#define iVersionControl VersionControl::getSingletonPtr()

#endif // VERSION_CONTROL_H
