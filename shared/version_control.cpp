#include "version_control.h"

initialiseSingleton ( VersionControl );

string VCBase::getVersion()
{
    return "Version control system not using";
}
GitVC::GitVC()
{
    FILE *fp;
    int len;
    char *buf;
    char *find_buf;
    char *last_ver_ptr;
    char version[128];
    char str_file[] = "../.git/logs/HEAD";

    fp=fopen(str_file,"rb");
    if (fp)
    {
        fseek(fp, 0, SEEK_END); ///go to end
        len=ftell(fp) + 2; ///get position at end (length) + reserved 2 bytes
        fseek(fp, 0, SEEK_SET); ///go to begin.
        buf=(char *)malloc(len); ///malloc buffer
        memset(buf, 0, len);
        fread(buf, len, 1, fp); ///read into buffer
        fclose(fp);
	find_buf = strstr(buf, "commit:");
	while(find_buf)
	{
	  last_ver_ptr = find_buf;
	  find_buf = strstr(find_buf + 1, "commit:");
	}
	sscanf(last_ver_ptr - 17, "%s ", version);
	_minor_version = version;
	free(buf);
    }
    else
    {
        traceerr("GIT config file = %s, load error", str_file);
    }
    _build_version = intToString(time(NULL));
    _major_version = MAJOR_VERSION;
    _full_version = _major_version + _minor_version;
}
string GitVC::getVersion()
{
    return _full_version;
}
VersionControl::VersionControl()
{
    vc = NULL;
    vcs_name = iConfig->getParam(Config::LS_VERSION_CONTROL_SYSTEM);
    if (vcs_name.find(VCS_GIT) != string::npos)
    {
        vc = new GitVC;
    }
}
string VersionControl::getVersion()
{
    if (!vc)
    {
        traceerr("No VCS specified!");
        return ((VCBase*)this)->getVersion();
    }
    return vc->getVersion();
}



