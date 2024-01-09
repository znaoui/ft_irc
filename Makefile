NAME = ircserv
SRC	= ircserv.cpp server/channel.cpp server/server.cpp utils/logger.cpp utils/type_conv.cpp commands/command_handler.cpp \
server/messages/err_msg.cpp server/messages/rpl_msg.cpp server/messages/broadcast_msg.cpp server/messages/cmd_msg.cpp \
commands/impl/nick.cpp commands/impl/user.cpp commands/impl/pass.cpp commands/impl/cap.cpp \
commands/impl/ping.cpp commands/impl/join.cpp commands/impl/quit.cpp commands/impl/privmsg.cpp \
commands/impl/part.cpp commands/impl/notice.cpp commands/impl/away.cpp commands/impl/motd.cpp \
commands/impl/kill.cpp commands/impl/oper.cpp commands/impl/kick.cpp commands/impl/who.cpp \
commands/impl/whois.cpp commands/impl/topic.cpp commands/impl/mode.cpp commands/impl/invite.cpp \
commands/impl/squit.cpp

OBJS = $(addprefix ft_irc/, ${SRC:.cpp=.o})
DEPS = $(addprefix ft_irc/, ${SRC:.cpp=.d})

RM = rm -f
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

all: 	${NAME}

${NAME}:	${OBJS}
		${CC} -o ${NAME} ${OBJS}

-include ${DEPS}

%.o: %.cpp Makefile
	${CC} ${CFLAGS} -MMD -MP -I./includes -c $< -o ${<:.cpp=.o}

clean:
		${RM} ircserv.log
		${RM} ${OBJS} ${DEPS}

fclean:	clean
		${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
