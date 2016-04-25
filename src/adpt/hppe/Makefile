LOC_DIR=src/adpt/hppe
LIB=ADPT

include $(PRJ_PATH)/make/config.mk

SRC_LIST=adpt_hppe_fdb.c adpt_hppe_mib.c adpt_hppe_stp.c adpt_hppe_vsi.c adpt_hppe_portctrl.c

ifeq (, $(findstring HPPE, $(SUPPORT_CHIP)))
  SRC_LIST=
endif

include $(PRJ_PATH)/make/components.mk
include $(PRJ_PATH)/make/defs.mk
include $(PRJ_PATH)/make/target.mk

all: dep obj
