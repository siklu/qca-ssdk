LOC_DIR=src/hsl/hppe
LIB=HSL

include $(PRJ_PATH)/make/config.mk

SRC_LIST=hppe_reg_access.c hppe_ip.c hppe_flow.c
SRC_LIST+=hppe_qm.c hppe_qos.c
SRC_LIST+=hppe_vsi.c hppe_fdb.c hppe_stp.c
SRC_LIST+=hppe_sec.c
SRC_LIST+=hppe_bm.c

ifeq (, $(findstring HPPE, $(SUPPORT_CHIP)))
  SRC_LIST=
endif

include $(PRJ_PATH)/make/components.mk
include $(PRJ_PATH)/make/defs.mk
include $(PRJ_PATH)/make/target.mk

all: dep obj
