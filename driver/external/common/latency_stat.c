#include <limits.h>
#include <float.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "latency_stat.h"
//#define HISTOGRAM

unsigned long long bucket_values[] =
	{     1,      2,      3,      4,      5,      6,      7,      8,      9,     10,
	     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,
	     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,
	     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,
	     41,     42,     43,     44,     45,     46,     47,     48,     49,     50,
	     51,     52,     53,     54,     55,     56,     57,     58,     59,     60,
	     61,     62,     63,     64,     65,     66,     67,     68,     69,     70,
	     71,     72,     73,     74,     75,     76,     77,     78,     79,     80,
	     81,     82,     83,     84,     85,     86,     87,     88,     89,     90,
	     91,     92,     93,     94,     95,     96,     97,     98,     99,    100,
	    102,    104,    106,    108,    110,    112,    114,    116,    118,    120,
	    122,    124,    126,    128,    130,    132,    134,    136,    138,    140,
	    142,    144,    146,    148,    150,    152,    154,    156,    158,    160,
	    162,    164,    166,    168,    170,    172,    174,    176,    178,    180,
	    182,    184,    186,    188,    190,    192,    194,    196,    198,    200,
	    205,    210,    215,    220,    225,    230,    235,    240,    245,    250,
	    255,    260,    265,    270,    275,    280,    285,    290,    295,    300,
	    305,    310,    315,    320,    325,    330,    335,    340,    345,    350,
	    355,    360,    365,    370,    375,    380,    385,    390,    395,    400,
	    405,    410,    415,    420,    425,    430,    435,    440,    445,    450,
	    455,    460,    465,    470,    475,    480,    485,    490,    495,    500,
	    510,    520,    530,    540,    550,    560,    570,    580,    590,    600,
	    610,    620,    630,    640,    650,    660,    670,    680,    690,    700,
	    710,    720,    730,    740,    750,    760,    770,    780,    790,    800,
	    810,    820,    830,    840,    850,    860,    870,    880,    890,    900,
	    910,    920,    930,    940,    950,    960,    970,    980,    990,   1000,
	   1020,   1040,   1060,   1080,   1100,   1120,   1140,   1160,   1180,   1200,
	   1220,   1240,   1260,   1280,   1300,   1320,   1340,   1360,   1380,   1400,
	   1420,   1440,   1460,   1480,   1500,   1520,   1540,   1560,   1580,   1600,
	   1620,   1640,   1660,   1680,   1700,   1720,   1740,   1760,   1780,   1800,
	   1820,   1840,   1860,   1880,   1900,   1920,   1940,   1960,   1980,   2000,
	   2050,   2100,   2150,   2200,   2250,   2300,   2350,   2400,   2450,   2500,
	   2550,   2600,   2650,   2700,   2750,   2800,   2850,   2900,   2950,   3000,
	   3050,   3100,   3150,   3200,   3250,   3300,   3350,   3400,   3450,   3500,
	   3550,   3600,   3650,   3700,   3750,   3800,   3850,   3900,   3950,   4000,
	   4050,   4100,   4150,   4200,   4250,   4300,   4350,   4400,   4450,   4500,
	   4550,   4600,   4650,   4700,   4750,   4800,   4850,   4900,   4950,   5000,
	   5100,   5200,   5300,   5400,   5500,   5600,   5700,   5800,   5900,   6000,
	   6100,   6200,   6300,   6400,   6500,   6600,   6700,   6800,   6900,   7000,
	   7100,   7200,   7300,   7400,   7500,   7600,   7700,   7800,   7900,   8000,
	   8100,   8200,   8300,   8400,   8500,   8600,   8700,   8800,   8900,   9000,
	   9100,   9200,   9300,   9400,   9500,   9600,   9700,   9800,   9900,  10000,
	  10200,  10400,  10600,  10800,  11000,  11200,  11400,  11600,  11800,  12000,
	  12200,  12400,  12600,  12800,  13000,  13200,  13400,  13600,  13800,  14000,
	  14200,  14400,  14600,  14800,  15000,  15200,  15400,  15600,  15800,  16000,
	  16200,  16400,  16600,  16800,  17000,  17200,  17400,  17600,  17800,  18000,
	  18200,  18400,  18600,  18800,  19000,  19200,  19400,  19600,  19800,  20000,
	  20500,  21000,  21500,  22000,  22500,  23000,  23500,  24000,  24500,  25000,
	  25500,  26000,  26500,  27000,  27500,  28000,  28500,  29000,  29500,  30000,
	  30500,  31000,  31500,  32000,  32500,  33000,  33500,  34000,  34500,  35000,
	  35500,  36000,  36500,  37000,  37500,  38000,  38500,  39000,  39500,  40000,
	  40500,  41000,  41500,  42000,  42500,  43000,  43500,  44000,  44500,  45000,
	  45500,  46000,  46500,  47000,  47500,  48000,  48500,  49000,  49500,  50000,
	  51000,  52000,  53000,  54000,  55000,  56000,  57000,  58000,  59000,  60000,
	  61000,  62000,  63000,  64000,  65000,  66000,  67000,  68000,  69000,  70000,
	  71000,  72000,  73000,  74000,  75000,  76000,  77000,  78000,  79000,  80000,
	  81000,  82000,  83000,  84000,  85000,  86000,  87000,  88000,  89000,  90000,
	  91000,  92000,  93000,  94000,  95000,  96000,  97000,  98000,  99000, 100000,
	 102000, 104000, 106000, 108000, 110000, 112000, 114000, 116000, 118000, 120000,
	 122000, 124000, 126000, 128000, 130000, 132000, 134000, 136000, 138000, 140000,
	 142000, 144000, 146000, 148000, 150000, 152000, 154000, 156000, 158000, 160000,
	 162000, 164000, 166000, 168000, 170000, 172000, 174000, 176000, 178000, 180000,
	 182000, 184000, 186000, 188000, 190000, 192000, 194000, 196000, 198000, 200000,
	 205000, 210000, 215000, 220000, 225000, 230000, 235000, 240000, 245000, 250000,
	 255000, 260000, 265000, 270000, 275000, 280000, 285000, 290000, 295000, 300000,
	 305000, 310000, 315000, 320000, 325000, 330000, 335000, 340000, 345000, 350000,
	 355000, 360000, 365000, 370000, 375000, 380000, 385000, 390000, 395000, 400000,
	 405000, 410000, 415000, 420000, 425000, 430000, 435000, 440000, 445000, 450000,
	 455000, 460000, 465000, 470000, 475000, 480000, 485000, 490000, 495000, 500000,
	 510000, 520000, 530000, 540000, 550000, 560000, 570000, 580000, 590000, 600000,
	 610000, 620000, 630000, 640000, 650000, 660000, 670000, 680000, 690000, 700000,
	 710000, 720000, 730000, 740000, 750000, 760000, 770000, 780000, 790000, 800000,
	 810000, 820000, 830000, 840000, 850000, 860000, 870000, 880000, 890000, 900000,
	 910000, 920000, 930000, 940000, 950000, 960000, 970000, 980000, 990000,1000000,
	1020000,1040000,1060000,1080000,1100000,1120000,1140000,1160000,1180000,1200000,
	1220000,1240000,1260000,1280000,1300000,1320000,1340000,1360000,1380000,1400000,
	1420000,1440000,1460000,1480000,1500000,1520000,1540000,1560000,1580000,1600000,
	1620000,1640000,1660000,1680000,1700000,1720000,1740000,1760000,1780000,1800000,
	1820000,1840000,1860000,1880000,1900000,1920000,1940000,1960000,1980000,2000000 };

#define MIN_BUCKET_VALUE (1ull)
#define MAX_BUCKET_VALUE (2000000ull)

void reset_latency_stat(struct latency_stat *stat) {
	stat->max = 0;
	stat->min = ULLONG_MAX;
	stat->samples = 0;
	stat->mean = 0;
	stat->variance = 0;
	stat->sum = 0;
	memset(stat->count_for_bucket, 0, sizeof(unsigned int)*BUCKET_SIZE);
}

int index_for_latency(unsigned long long latency){
	int ret = -1;
	int first = 0;
	int last = BUCKET_SIZE-1;
	int mid = 0;

	if (latency >= MAX_BUCKET_VALUE){
		ret = BUCKET_SIZE - 1;
	} else if (latency < MIN_BUCKET_VALUE){
		ret = 0;
	} else {
		while (first <= last){
			mid = (first + last)/2;
			if (latency >= bucket_values[mid]) {
				first = mid + 1;
			} else {
				if (latency >= bucket_values[mid-1]){
					return mid;
				}
				last = mid - 1;
			}
		}
	}
	return ret;
}

double latency_percentile(struct latency_stat *stat, double p){
	//referenced from db_bench of RocksDB
	double threshold = stat->samples * p;
	uint32_t cumulative_sum = 0;
	uint32_t bucket_count = 0;
	for (unsigned int i= 0; i < BUCKET_SIZE; i++) {
		bucket_count = stat->count_for_bucket[i];
		cumulative_sum += bucket_count;
		if (cumulative_sum >= threshold) {
			// Scale linearly within this bucket
			unsigned long long left_point = (i == 0) ? 0 : bucket_values[i-1];
			unsigned long long right_point = bucket_values[i];
			//debug
			//printf("\np=%f, left=%llu, right=%llu, cum=%u, th=%.1f\n", p, left_point, right_point, cumulative_sum, threshold);
			uint32_t left_sum = cumulative_sum - bucket_count;
			uint32_t right_sum = cumulative_sum;
			double pos = 0;
			uint32_t right_left_diff = right_sum - left_sum;
			if (right_left_diff != 0) {
				pos = (threshold - left_sum) / right_left_diff;
			}
			double r = left_point + (right_point - left_point) * pos;
			unsigned long long cur_min = stat->min;
			unsigned long long cur_max = stat->max;
			if (r < cur_min) r = (double)cur_min;
			if (r > cur_max) r = (double)cur_max;
			return r;
		}
	}
	return (double)stat->max;
}

void add_latency_stat(struct latency_stat *stat, const struct timeval *start, const struct timeval *end) {
	long long sec = end->tv_sec - start->tv_sec;
	long long usec = end->tv_usec - start->tv_usec;
	unsigned long long latency;
	//double delta;

	if ((sec > 0) && (usec < 0)) {
		--sec;
		usec += 1000000;
	}
	assert(!((sec < 0) || ((sec == 0) && (usec < 0))));

	latency = sec * 1000000ull + usec;
	if (latency > stat->max)
		stat->max = latency;
	if (latency < stat->min)
		stat->min = latency;

	stat->sum += latency;
	stat->count_for_bucket[index_for_latency(latency)]++;

	/* reference
	 * https://en.wikipedia.org/wiki/Algorithm_for_calculating_variance
	 * Online algorithm */
	//delta = (double)latency - stat->mean;
	//if (delta) {
	//	stat->mean += delta / (stat->samples + 1.0);
	//	stat->variance += delta * ((double)latency - stat->mean);
	//}
	++stat->samples;
}

/* reference
 * https://www.johndcook.com/blog/cpp_phi_inverse
 * Normal CDF Inverse */

double RationalApproximation(double t) {
	// Abramwitz and Stegun formula 26.2.23.
	// The absolute value of the error should be less than 4.5 e-4.
	const double c[] = {2.515517, 0.802853, 0.010328};
	const double d[] = {1.432788, 0.189269, 0.001308};
	return t - ((c[2]*t + c[1])*t + c[0]) / (((d[2]*t + d[1])*t +d[0])*t + 1.0);
}

double NormalCDFInverse(double p) {
	assert(!((p <= 0.0) || (p >= 1.0)));
	// See article above for explanation of this section.
	if (p < 0.5) {
		// F^-1(p) = -G^-1(p)
		return -RationalApproximation(sqrt(-2.0*log(p)));
	} else {
		// F^-1(p) = G^-1(1-p)
		return RationalApproximation(sqrt(-2.0 * log(1-p)));
	}
}

void print_latency_stat(struct latency_stat *stat) {
	//double stdev;
	const double p[] = {0.01, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,
		0.8, 0.9, 0.95, 0.99, 0.995, 0.999, 0.9995, 0.9999};
	//double v[] = {0.00, 0.00, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
	//	0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	//double min_v = DBL_MAX;
	int i;

	if ((stat->samples == 0) || (stat->samples == 1))
		return;

	//stdev = sqrt(stat->variance / (stat->samples - 1.0));
	//printf("     lat(usec): min=%llu, max=%llu, mean=%.3f, stdev=%.3f\n", stat->min, stat->max, stat->mean, stdev);
	printf("     lat(usec): min=%llu, max=%llu, mean=%.3f\n", stat->min, stat->max, stat->sum/(double)stat->samples);
	printf("     lat percentiles (usec):");

	/* for elminating minus value */
	//for (i = 0; i < (int)(sizeof(p)/sizeof(p[0])); i++) {
	//	v[i] = NormalCDFInverse(p[i]) * stdev + stat->mean;
	//	if (v[i] > 0 && min_v > v[i])
	//		min_v = v[i];
	//}

	for (i = 0; i < (int)(sizeof(p)/sizeof(p[0])); i++) {
		if (i % 4 == 0)
			printf("\n     |");
		//double value = v[i];
		//if (value < 0) value = min_v < stat->min ? min_v : stat->min;
		double value = latency_percentile(stat, p[i]);
		if (i == 0 || i == 1)
			printf(" %4.2f%%=[%5.0f] ", p[i]*100, value);
		else
			printf("%4.2f%%=[%5.0f] ", p[i]*100, value);
	}
	printf("\n");

#ifdef HISTOGRAM
	/* for detail info */
	printf("\n     # of operations for latencies:\n");
	for (unsigned i = 0; i < BUCKET_SIZE; i++){
		if (!stat->count_for_bucket[i]) continue;
		if (i != 0) {
			printf("     [%7llu, %7llu): %u\n", bucket_values[i-1], bucket_values[i], stat->count_for_bucket[i]);
		} else {
			printf("     [%7llu, %7llu): %u\n", 0ull, bucket_values[i], stat->count_for_bucket[i]);
		}
	}
#endif
}
