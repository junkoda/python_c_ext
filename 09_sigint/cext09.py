import signal
import sys
import cext09

import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)

cext09.long_computation()
