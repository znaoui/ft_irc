#include <string>
#include <limits.h>

struct channel_mode {
	bool onlyInvite;
	bool topicCmd;
	bool turnChannelKey;
	bool noOpMode;
	std::string password;
	bool limitUser;
	int  nbMaxUser;

	channel_mode(): onlyInvite(false), topicCmd(false), turnChannelKey(false), noOpMode(false), limitUser(false), nbMaxUser(INT_MAX){};
};