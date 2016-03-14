LOC_DIR=src/hsl/hppe
LIB=HSL

include $(PRJ_PATH)/make/config.mk

SRC_LIST=hppe_l3_api.c hppe_reg_access.c

ifeq (, $(findstring HPPE, $(SUPPORT_CHIP)))
  SRC_LIST=
endif

include $(PRJ_PATH)/make/components.mk
include $(PRJ_PATH)/make/defs.mk
include $(PRJ_PATH)/make/target.mk

all: dep obj
