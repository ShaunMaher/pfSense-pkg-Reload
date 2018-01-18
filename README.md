# Reload
This **will be** a simple package that can be installed into pfSense that allows
an administrator to schedule a rollback of the pfSense configuration.  The
general idea is to help avoid situations where you lock yourself out of a remote
device.

Before you begin making changes, schedule a reload to the current configuration
to occur in 10-120 minutes time.  Make your desired changes within selected time
window and then cancel the reload.  If, during the process, you managed to lock
yourself out of the device you know that a reload is going to occur which will
take you back to a known good configuration.

Note the "**will be**".  At the moment this is an empty framework waiting to
have code added.   
