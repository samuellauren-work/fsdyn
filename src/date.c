#include "date.h"

#include "fsdyn_version.h"

typedef struct {
    int year_offset;
    int month; /* 0 = January */
    int mday;  /* 1..31 */
} yday_info_t;

static const yday_info_t YDAY_INFO[];

struct tm *epoch_to_utc(time_t epoch, struct tm *tm)
{
    enum {
        SECONDS_PER_DAY = 86400,
        FROM_1600_03_01 = 135080, /* days from 1600-03-01 to 1970-01-01 */
        YEAR = 365,
        CENTURY = 100 * YEAR + 24,
        _400_YEARS = 4 * CENTURY + 1,
        _4_YEARS = 4 * YEAR + 1,
        FEBRUARY = 1 /* sic */
    };
    tm->tm_sec = epoch % SECONDS_PER_DAY;
    tm->tm_min = tm->tm_sec / 60;
    tm->tm_sec %= 60;
    tm->tm_hour = tm->tm_min / 60;
    tm->tm_min %= 60;
    tm->tm_yday = -1; /* not supported */
    tm->tm_isdst = 0;
    int days = epoch / SECONDS_PER_DAY;
    tm->tm_wday = (days + 4) % 7;
    days += FROM_1600_03_01;
    tm->tm_year = 1600 + days / _400_YEARS * 400 - 1900;
    days %= _400_YEARS;
    int centuries = days / CENTURY;
    tm->tm_year += centuries * 100;
    if (centuries == 4) {
        tm->tm_mon = FEBRUARY;
        tm->tm_mday = 29;
        return tm;
    }
    days %= CENTURY;
    tm->tm_year += days / _4_YEARS * 4;
    days %= _4_YEARS;
    int years = days / YEAR;
    tm->tm_year += years;
    if (years == 4) {
        tm->tm_mon = FEBRUARY;
        tm->tm_mday = 29;
        return tm;
    }
    days %= YEAR; /* 1 Jan = 0 */
    const yday_info_t *info = &YDAY_INFO[days];
    tm->tm_year += info->year_offset;
    tm->tm_mon = info->month;
    tm->tm_mday = info->mday;
    return tm;
}

static const yday_info_t YDAY_INFO[] = {
    { 0, 2, 1 },   /* 0 */
    { 0, 2, 2 },   /* 1 */
    { 0, 2, 3 },   /* 2 */
    { 0, 2, 4 },   /* 3 */
    { 0, 2, 5 },   /* 4 */
    { 0, 2, 6 },   /* 5 */
    { 0, 2, 7 },   /* 6 */
    { 0, 2, 8 },   /* 7 */
    { 0, 2, 9 },   /* 8 */
    { 0, 2, 10 },  /* 9 */
    { 0, 2, 11 },  /* 10 */
    { 0, 2, 12 },  /* 11 */
    { 0, 2, 13 },  /* 12 */
    { 0, 2, 14 },  /* 13 */
    { 0, 2, 15 },  /* 14 */
    { 0, 2, 16 },  /* 15 */
    { 0, 2, 17 },  /* 16 */
    { 0, 2, 18 },  /* 17 */
    { 0, 2, 19 },  /* 18 */
    { 0, 2, 20 },  /* 19 */
    { 0, 2, 21 },  /* 20 */
    { 0, 2, 22 },  /* 21 */
    { 0, 2, 23 },  /* 22 */
    { 0, 2, 24 },  /* 23 */
    { 0, 2, 25 },  /* 24 */
    { 0, 2, 26 },  /* 25 */
    { 0, 2, 27 },  /* 26 */
    { 0, 2, 28 },  /* 27 */
    { 0, 2, 29 },  /* 28 */
    { 0, 2, 30 },  /* 29 */
    { 0, 2, 31 },  /* 30 */
    { 0, 3, 1 },   /* 31 */
    { 0, 3, 2 },   /* 32 */
    { 0, 3, 3 },   /* 33 */
    { 0, 3, 4 },   /* 34 */
    { 0, 3, 5 },   /* 35 */
    { 0, 3, 6 },   /* 36 */
    { 0, 3, 7 },   /* 37 */
    { 0, 3, 8 },   /* 38 */
    { 0, 3, 9 },   /* 39 */
    { 0, 3, 10 },  /* 40 */
    { 0, 3, 11 },  /* 41 */
    { 0, 3, 12 },  /* 42 */
    { 0, 3, 13 },  /* 43 */
    { 0, 3, 14 },  /* 44 */
    { 0, 3, 15 },  /* 45 */
    { 0, 3, 16 },  /* 46 */
    { 0, 3, 17 },  /* 47 */
    { 0, 3, 18 },  /* 48 */
    { 0, 3, 19 },  /* 49 */
    { 0, 3, 20 },  /* 50 */
    { 0, 3, 21 },  /* 51 */
    { 0, 3, 22 },  /* 52 */
    { 0, 3, 23 },  /* 53 */
    { 0, 3, 24 },  /* 54 */
    { 0, 3, 25 },  /* 55 */
    { 0, 3, 26 },  /* 56 */
    { 0, 3, 27 },  /* 57 */
    { 0, 3, 28 },  /* 58 */
    { 0, 3, 29 },  /* 59 */
    { 0, 3, 30 },  /* 60 */
    { 0, 4, 1 },   /* 61 */
    { 0, 4, 2 },   /* 62 */
    { 0, 4, 3 },   /* 63 */
    { 0, 4, 4 },   /* 64 */
    { 0, 4, 5 },   /* 65 */
    { 0, 4, 6 },   /* 66 */
    { 0, 4, 7 },   /* 67 */
    { 0, 4, 8 },   /* 68 */
    { 0, 4, 9 },   /* 69 */
    { 0, 4, 10 },  /* 70 */
    { 0, 4, 11 },  /* 71 */
    { 0, 4, 12 },  /* 72 */
    { 0, 4, 13 },  /* 73 */
    { 0, 4, 14 },  /* 74 */
    { 0, 4, 15 },  /* 75 */
    { 0, 4, 16 },  /* 76 */
    { 0, 4, 17 },  /* 77 */
    { 0, 4, 18 },  /* 78 */
    { 0, 4, 19 },  /* 79 */
    { 0, 4, 20 },  /* 80 */
    { 0, 4, 21 },  /* 81 */
    { 0, 4, 22 },  /* 82 */
    { 0, 4, 23 },  /* 83 */
    { 0, 4, 24 },  /* 84 */
    { 0, 4, 25 },  /* 85 */
    { 0, 4, 26 },  /* 86 */
    { 0, 4, 27 },  /* 87 */
    { 0, 4, 28 },  /* 88 */
    { 0, 4, 29 },  /* 89 */
    { 0, 4, 30 },  /* 90 */
    { 0, 4, 31 },  /* 91 */
    { 0, 5, 1 },   /* 92 */
    { 0, 5, 2 },   /* 93 */
    { 0, 5, 3 },   /* 94 */
    { 0, 5, 4 },   /* 95 */
    { 0, 5, 5 },   /* 96 */
    { 0, 5, 6 },   /* 97 */
    { 0, 5, 7 },   /* 98 */
    { 0, 5, 8 },   /* 99 */
    { 0, 5, 9 },   /* 100 */
    { 0, 5, 10 },  /* 101 */
    { 0, 5, 11 },  /* 102 */
    { 0, 5, 12 },  /* 103 */
    { 0, 5, 13 },  /* 104 */
    { 0, 5, 14 },  /* 105 */
    { 0, 5, 15 },  /* 106 */
    { 0, 5, 16 },  /* 107 */
    { 0, 5, 17 },  /* 108 */
    { 0, 5, 18 },  /* 109 */
    { 0, 5, 19 },  /* 110 */
    { 0, 5, 20 },  /* 111 */
    { 0, 5, 21 },  /* 112 */
    { 0, 5, 22 },  /* 113 */
    { 0, 5, 23 },  /* 114 */
    { 0, 5, 24 },  /* 115 */
    { 0, 5, 25 },  /* 116 */
    { 0, 5, 26 },  /* 117 */
    { 0, 5, 27 },  /* 118 */
    { 0, 5, 28 },  /* 119 */
    { 0, 5, 29 },  /* 120 */
    { 0, 5, 30 },  /* 121 */
    { 0, 6, 1 },   /* 122 */
    { 0, 6, 2 },   /* 123 */
    { 0, 6, 3 },   /* 124 */
    { 0, 6, 4 },   /* 125 */
    { 0, 6, 5 },   /* 126 */
    { 0, 6, 6 },   /* 127 */
    { 0, 6, 7 },   /* 128 */
    { 0, 6, 8 },   /* 129 */
    { 0, 6, 9 },   /* 130 */
    { 0, 6, 10 },  /* 131 */
    { 0, 6, 11 },  /* 132 */
    { 0, 6, 12 },  /* 133 */
    { 0, 6, 13 },  /* 134 */
    { 0, 6, 14 },  /* 135 */
    { 0, 6, 15 },  /* 136 */
    { 0, 6, 16 },  /* 137 */
    { 0, 6, 17 },  /* 138 */
    { 0, 6, 18 },  /* 139 */
    { 0, 6, 19 },  /* 140 */
    { 0, 6, 20 },  /* 141 */
    { 0, 6, 21 },  /* 142 */
    { 0, 6, 22 },  /* 143 */
    { 0, 6, 23 },  /* 144 */
    { 0, 6, 24 },  /* 145 */
    { 0, 6, 25 },  /* 146 */
    { 0, 6, 26 },  /* 147 */
    { 0, 6, 27 },  /* 148 */
    { 0, 6, 28 },  /* 149 */
    { 0, 6, 29 },  /* 150 */
    { 0, 6, 30 },  /* 151 */
    { 0, 6, 31 },  /* 152 */
    { 0, 7, 1 },   /* 153 */
    { 0, 7, 2 },   /* 154 */
    { 0, 7, 3 },   /* 155 */
    { 0, 7, 4 },   /* 156 */
    { 0, 7, 5 },   /* 157 */
    { 0, 7, 6 },   /* 158 */
    { 0, 7, 7 },   /* 159 */
    { 0, 7, 8 },   /* 160 */
    { 0, 7, 9 },   /* 161 */
    { 0, 7, 10 },  /* 162 */
    { 0, 7, 11 },  /* 163 */
    { 0, 7, 12 },  /* 164 */
    { 0, 7, 13 },  /* 165 */
    { 0, 7, 14 },  /* 166 */
    { 0, 7, 15 },  /* 167 */
    { 0, 7, 16 },  /* 168 */
    { 0, 7, 17 },  /* 169 */
    { 0, 7, 18 },  /* 170 */
    { 0, 7, 19 },  /* 171 */
    { 0, 7, 20 },  /* 172 */
    { 0, 7, 21 },  /* 173 */
    { 0, 7, 22 },  /* 174 */
    { 0, 7, 23 },  /* 175 */
    { 0, 7, 24 },  /* 176 */
    { 0, 7, 25 },  /* 177 */
    { 0, 7, 26 },  /* 178 */
    { 0, 7, 27 },  /* 179 */
    { 0, 7, 28 },  /* 180 */
    { 0, 7, 29 },  /* 181 */
    { 0, 7, 30 },  /* 182 */
    { 0, 7, 31 },  /* 183 */
    { 0, 8, 1 },   /* 184 */
    { 0, 8, 2 },   /* 185 */
    { 0, 8, 3 },   /* 186 */
    { 0, 8, 4 },   /* 187 */
    { 0, 8, 5 },   /* 188 */
    { 0, 8, 6 },   /* 189 */
    { 0, 8, 7 },   /* 190 */
    { 0, 8, 8 },   /* 191 */
    { 0, 8, 9 },   /* 192 */
    { 0, 8, 10 },  /* 193 */
    { 0, 8, 11 },  /* 194 */
    { 0, 8, 12 },  /* 195 */
    { 0, 8, 13 },  /* 196 */
    { 0, 8, 14 },  /* 197 */
    { 0, 8, 15 },  /* 198 */
    { 0, 8, 16 },  /* 199 */
    { 0, 8, 17 },  /* 200 */
    { 0, 8, 18 },  /* 201 */
    { 0, 8, 19 },  /* 202 */
    { 0, 8, 20 },  /* 203 */
    { 0, 8, 21 },  /* 204 */
    { 0, 8, 22 },  /* 205 */
    { 0, 8, 23 },  /* 206 */
    { 0, 8, 24 },  /* 207 */
    { 0, 8, 25 },  /* 208 */
    { 0, 8, 26 },  /* 209 */
    { 0, 8, 27 },  /* 210 */
    { 0, 8, 28 },  /* 211 */
    { 0, 8, 29 },  /* 212 */
    { 0, 8, 30 },  /* 213 */
    { 0, 9, 1 },   /* 214 */
    { 0, 9, 2 },   /* 215 */
    { 0, 9, 3 },   /* 216 */
    { 0, 9, 4 },   /* 217 */
    { 0, 9, 5 },   /* 218 */
    { 0, 9, 6 },   /* 219 */
    { 0, 9, 7 },   /* 220 */
    { 0, 9, 8 },   /* 221 */
    { 0, 9, 9 },   /* 222 */
    { 0, 9, 10 },  /* 223 */
    { 0, 9, 11 },  /* 224 */
    { 0, 9, 12 },  /* 225 */
    { 0, 9, 13 },  /* 226 */
    { 0, 9, 14 },  /* 227 */
    { 0, 9, 15 },  /* 228 */
    { 0, 9, 16 },  /* 229 */
    { 0, 9, 17 },  /* 230 */
    { 0, 9, 18 },  /* 231 */
    { 0, 9, 19 },  /* 232 */
    { 0, 9, 20 },  /* 233 */
    { 0, 9, 21 },  /* 234 */
    { 0, 9, 22 },  /* 235 */
    { 0, 9, 23 },  /* 236 */
    { 0, 9, 24 },  /* 237 */
    { 0, 9, 25 },  /* 238 */
    { 0, 9, 26 },  /* 239 */
    { 0, 9, 27 },  /* 240 */
    { 0, 9, 28 },  /* 241 */
    { 0, 9, 29 },  /* 242 */
    { 0, 9, 30 },  /* 243 */
    { 0, 9, 31 },  /* 244 */
    { 0, 10, 1 },  /* 245 */
    { 0, 10, 2 },  /* 246 */
    { 0, 10, 3 },  /* 247 */
    { 0, 10, 4 },  /* 248 */
    { 0, 10, 5 },  /* 249 */
    { 0, 10, 6 },  /* 250 */
    { 0, 10, 7 },  /* 251 */
    { 0, 10, 8 },  /* 252 */
    { 0, 10, 9 },  /* 253 */
    { 0, 10, 10 }, /* 254 */
    { 0, 10, 11 }, /* 255 */
    { 0, 10, 12 }, /* 256 */
    { 0, 10, 13 }, /* 257 */
    { 0, 10, 14 }, /* 258 */
    { 0, 10, 15 }, /* 259 */
    { 0, 10, 16 }, /* 260 */
    { 0, 10, 17 }, /* 261 */
    { 0, 10, 18 }, /* 262 */
    { 0, 10, 19 }, /* 263 */
    { 0, 10, 20 }, /* 264 */
    { 0, 10, 21 }, /* 265 */
    { 0, 10, 22 }, /* 266 */
    { 0, 10, 23 }, /* 267 */
    { 0, 10, 24 }, /* 268 */
    { 0, 10, 25 }, /* 269 */
    { 0, 10, 26 }, /* 270 */
    { 0, 10, 27 }, /* 271 */
    { 0, 10, 28 }, /* 272 */
    { 0, 10, 29 }, /* 273 */
    { 0, 10, 30 }, /* 274 */
    { 0, 11, 1 },  /* 275 */
    { 0, 11, 2 },  /* 276 */
    { 0, 11, 3 },  /* 277 */
    { 0, 11, 4 },  /* 278 */
    { 0, 11, 5 },  /* 279 */
    { 0, 11, 6 },  /* 280 */
    { 0, 11, 7 },  /* 281 */
    { 0, 11, 8 },  /* 282 */
    { 0, 11, 9 },  /* 283 */
    { 0, 11, 10 }, /* 284 */
    { 0, 11, 11 }, /* 285 */
    { 0, 11, 12 }, /* 286 */
    { 0, 11, 13 }, /* 287 */
    { 0, 11, 14 }, /* 288 */
    { 0, 11, 15 }, /* 289 */
    { 0, 11, 16 }, /* 290 */
    { 0, 11, 17 }, /* 291 */
    { 0, 11, 18 }, /* 292 */
    { 0, 11, 19 }, /* 293 */
    { 0, 11, 20 }, /* 294 */
    { 0, 11, 21 }, /* 295 */
    { 0, 11, 22 }, /* 296 */
    { 0, 11, 23 }, /* 297 */
    { 0, 11, 24 }, /* 298 */
    { 0, 11, 25 }, /* 299 */
    { 0, 11, 26 }, /* 300 */
    { 0, 11, 27 }, /* 301 */
    { 0, 11, 28 }, /* 302 */
    { 0, 11, 29 }, /* 303 */
    { 0, 11, 30 }, /* 304 */
    { 0, 11, 31 }, /* 305 */
    { 1, 0, 1 },   /* 306 */
    { 1, 0, 2 },   /* 307 */
    { 1, 0, 3 },   /* 308 */
    { 1, 0, 4 },   /* 309 */
    { 1, 0, 5 },   /* 310 */
    { 1, 0, 6 },   /* 311 */
    { 1, 0, 7 },   /* 312 */
    { 1, 0, 8 },   /* 313 */
    { 1, 0, 9 },   /* 314 */
    { 1, 0, 10 },  /* 315 */
    { 1, 0, 11 },  /* 316 */
    { 1, 0, 12 },  /* 317 */
    { 1, 0, 13 },  /* 318 */
    { 1, 0, 14 },  /* 319 */
    { 1, 0, 15 },  /* 320 */
    { 1, 0, 16 },  /* 321 */
    { 1, 0, 17 },  /* 322 */
    { 1, 0, 18 },  /* 323 */
    { 1, 0, 19 },  /* 324 */
    { 1, 0, 20 },  /* 325 */
    { 1, 0, 21 },  /* 326 */
    { 1, 0, 22 },  /* 327 */
    { 1, 0, 23 },  /* 328 */
    { 1, 0, 24 },  /* 329 */
    { 1, 0, 25 },  /* 330 */
    { 1, 0, 26 },  /* 331 */
    { 1, 0, 27 },  /* 332 */
    { 1, 0, 28 },  /* 333 */
    { 1, 0, 29 },  /* 334 */
    { 1, 0, 30 },  /* 335 */
    { 1, 0, 31 },  /* 336 */
    { 1, 1, 1 },   /* 337 */
    { 1, 1, 2 },   /* 338 */
    { 1, 1, 3 },   /* 339 */
    { 1, 1, 4 },   /* 340 */
    { 1, 1, 5 },   /* 341 */
    { 1, 1, 6 },   /* 342 */
    { 1, 1, 7 },   /* 343 */
    { 1, 1, 8 },   /* 344 */
    { 1, 1, 9 },   /* 345 */
    { 1, 1, 10 },  /* 346 */
    { 1, 1, 11 },  /* 347 */
    { 1, 1, 12 },  /* 348 */
    { 1, 1, 13 },  /* 349 */
    { 1, 1, 14 },  /* 350 */
    { 1, 1, 15 },  /* 351 */
    { 1, 1, 16 },  /* 352 */
    { 1, 1, 17 },  /* 353 */
    { 1, 1, 18 },  /* 354 */
    { 1, 1, 19 },  /* 355 */
    { 1, 1, 20 },  /* 356 */
    { 1, 1, 21 },  /* 357 */
    { 1, 1, 22 },  /* 358 */
    { 1, 1, 23 },  /* 359 */
    { 1, 1, 24 },  /* 360 */
    { 1, 1, 25 },  /* 361 */
    { 1, 1, 26 },  /* 362 */
    { 1, 1, 27 },  /* 363 */
    { 1, 1, 28 },  /* 364 */
    { 1, 1, 29 },  /* 365 */
};
