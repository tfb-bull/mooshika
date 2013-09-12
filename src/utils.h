#define ERROR_LOG(fmt, args...) fprintf(stderr, "ERROR: %s (%d), %s: " fmt "\n", __FILE__, __LINE__, __func__, ##args)
//#define ERROR_LOG(fmt, args...)
#define INFO_LOG(debug, fmt, args...) 	if (debug) fprintf(stderr, "INFO:  %s (%d), %s: " fmt "\n", __FILE__, __LINE__, __func__, ##args)
//#define INFO_LOG(fmt, args...)


#define atomic_inc(x) __sync_fetch_and_add(&x, 1)
#define atomic_dec(x) __sync_fetch_and_sub(&x, 1)
#define atomic_add(x,i) __sync_fetch_and_add(&x, i)
#define atomic_sub(x,i) __sync_fetch_and_sub(&x, i)
#define atomic_mask(x,i) __sync_fetch_and_and(&x, i)

static inline int set_size(uint32_t *val, char *unit) {
	switch(unit[0]) {
		case 'k':
		case 'K':
			*val *= 1024;
			break;
		case 'm':
		case 'M':
			*val *= 1024 * 1024;
			break;
		case 'g':
		case 'G':
			*val *= 1024 * 1024 * 1024;
			break;
		default:
			ERROR_LOG("unknown unit '%c'", unit[0]);
			return EINVAL;
	}

	return 0;
}

static inline void sub_timespec(uint64_t *new, struct timespec *x, struct timespec *y) {
	if (y->tv_nsec < x->tv_nsec) {
		*new = (y->tv_sec - x->tv_sec - 1) * 1000000 +
			y->tv_nsec + 1000000 - x->tv_nsec;
	} else {
		*new = (y->tv_sec - x->tv_sec) * 1000000 +
			y->tv_nsec - x->tv_nsec;
	}
}
