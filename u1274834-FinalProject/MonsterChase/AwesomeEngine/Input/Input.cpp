#include "Input.h"
#include "GLib.h"

#include <assert.h>
#include <stdio.h>




namespace Engine {
	namespace Input {
		int dir = 0;
		void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
		{

			if (i_VKeyID == 87 && bWentDown) {
				dir = 1;
			}
			else if (i_VKeyID == 65 && bWentDown) {
				dir = 2;
			}
			else if (i_VKeyID == 83 && bWentDown) {
				dir = 3;
			}
			else if (i_VKeyID == 68 && bWentDown) {
				dir = 4;
			}
			else {
				dir = 0;
			}

		}

		int Read() {
			GLib::SetKeyStateChangeCallback(TestKeyCallback);
			return dir;
		}
	}
}
