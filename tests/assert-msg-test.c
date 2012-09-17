#include <glib.h>

#ifdef G_OS_WIN32
#include <windows.h>
#endif

int main(int argc, char **argv)
{
#ifdef G_OS_WIN32
  SetErrorMode (SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#endif

  g_assert(42 < 0);
  return 0;
}

