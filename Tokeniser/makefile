#Name
NAME = a.out

#directories
VPATH= Directive Parsing Utils Web_serv
OBJ_DIR = Obj

#Compilation
CC = c++
FLAG = -std=c++98 #-Wall -Wextra -Werror -g
OPT_NAME = -o $(NAME)
OPT_HEADER = -I. $(addprefix -I, $(VPATH))

#define
DEFINE =
LOG ?= "nolog"
LVL ?= -1

#clean
RM = rm -rf



SRC = ADirective.cpp Listen.cpp log.cpp MaxBodySize.cpp ServerName.cpp Common.cpp \
Methods.cpp Error_page.cpp Index.cpp Autoindex.cpp Return.cpp Cgi_ext.cpp Root.cpp
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o )
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAG) $(DEFINE) $(OBJ)  $(OPT_NAME)
	@echo Succeed : Compilation

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(FLAG) $(DEFINE) $(OPT_HEADER) -MMD -MP -c $< -o $@

-include $(DEP)

log:
	@./helper.sh "$(LOG)" "$(LVL)"
	$(MAKE) DEFINE="-D$(LOG)=$(LVL)" all

clean:
	$(RM) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re