LOC_DIR=src/adpt/hppe
LIB=ADPT

include $(PRJ_PATH)/make/config.mk


ifeq (TRUE, $(IN_FDB))
  SRC_LIST += adpt_hppe_fdb.c
endif

ifeq (TRUE, $(IN_MIB))
  SRC_LIST += adpt_hppe_mib.c
endif

ifeq (TRUE, $(IN_STP))
  SRC_LIST += adpt_hppe_stp.c
endif

ifeq (TRUE, $(IN_VSI))
  SRC_LIST += adpt_hppe_vsi.c
endif

ifeq (TRUE, $(IN_PORTCONTROL))
  SRC_LIST += adpt_hppe_portctrl.c
endif

ifeq (TRUE, $(IN_MIRROR))
  SRC_LIST += adpt_hppe_mirror.c
endif

ifeq (TRUE, $(IN_TRUNK))
  SRC_LIST += adpt_hppe_trunk.c
endif

ifeq (TRUE, $(IN_IP))
  SRC_LIST += adpt_hppe_ip.c
endif

ifeq (TRUE, $(IN_FLOW))
  SRC_LIST += adpt_hppe_flow.c
endif

ifeq (TRUE, $(IN_QM))
  SRC_LIST += adpt_hppe_qm.c
endif

ifeq (, $(findstring HPPE, $(SUPPORT_CHIP)))
  SRC_LIST=
endif

include $(PRJ_PATH)/make/components.mk
include $(PRJ_PATH)/make/defs.mk
include $(PRJ_PATH)/make/target.mk

all: dep obj
