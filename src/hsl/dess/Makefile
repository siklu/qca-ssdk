LOC_DIR=src/hsl/dess
LIB=HSL

include $(PRJ_PATH)/make/config.mk

SRC_LIST=dess_reg_access.c dess_init.c

ifeq (TRUE, $(IN_ACL))
  SRC_LIST += dess_acl.c dess_acl_parse.c
endif

ifeq (TRUE, $(IN_MIB))
  SRC_LIST += dess_mib.c
endif

ifeq (TRUE, $(IN_PORTVLAN))
  SRC_LIST += dess_portvlan.c
endif

ifeq (TRUE, $(IN_QOS))
  SRC_LIST += dess_qos.c
endif

ifeq (TRUE, $(IN_VLAN))
  SRC_LIST += dess_vlan.c

ifeq (TRUE, $(IN_COSMAP))
  SRC_LIST += dess_cosmap.c
endif

ifeq (TRUE, $(IN_SEC))
  SRC_LIST += dess_sec.c
endif

endif

ifeq (linux, $(OS))
	ifeq (KSLIB, $(MODULE_TYPE))
    ifneq (TRUE, $(KERNEL_MODE))
      SRC_LIST=dess_reg_access.c dess_init.c
	  endif
	endif
endif

ifeq (, $(findstring DESS, $(SUPPORT_CHIP)))
  SRC_LIST=
endif

include $(PRJ_PATH)/make/components.mk
include $(PRJ_PATH)/make/defs.mk
include $(PRJ_PATH)/make/target.mk

all: dep obj
