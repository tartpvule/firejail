#include "firejail.h"

char *net_prefix = "fjbr";
size_t net_prefix_len = 4;
char *vethname_prefix = "fjveth";
size_t vethname_prefix_len = 6;

int hasAllowed = 0;

int checkcfg2_initialize(const char *ptr) {
	if (strncmp(ptr, "cfg2-net-prefix ", 16) == 0) {
		net_prefix = strdup(ptr + 16);
		if (!net_prefix) {
			errExit("strdup");
		}
		net_prefix_len = strlen(net_prefix);
	} else if (strncmp(ptr, "cfg2-vethname-prefix ", 21) == 0) {
		vethname_prefix = strdup(ptr + 21);
		if (!vethname_prefix) {
			errExit("strdup");
		}
		vethname_prefix_len = strlen(vethname_prefix);
	} else {
		return 0;
	}
	return 1;
}

int checkcfg2_network(int cfg, const char *val) {
	if (checkcfg(CFG_NETWORK)) {
		return 1;
	} else if (!checkcfg(CFG_RESTRICTED_NETWORK)) {
		return 0;
	}

	if (cfg == CFG2_NET) {
		if (strncmp(net_prefix, val, net_prefix_len) == 0) {
			hasAllowed = 1;
			return 1;
		}
	} else if (cfg == CFG2_VETHNAME) {
		if (strncmp(vethname_prefix, val, vethname_prefix_len) == 0) {
			hasAllowed = 1;
			return 1;
		}
	} else {
		return hasAllowed;
	}

	return 0;
}
