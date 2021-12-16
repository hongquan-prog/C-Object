PRO_CFG := $(abspath pro-cfg.mk)
PRO_CMD := $(abspath pro-cmd.mk)
PRO_RULE := $(abspath pro-rule.mk)

include $(PRO_CFG)
include $(PRO_CMD)
include $(PRO_RULE)