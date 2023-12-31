#pragma once

# include <sys/types.h>
# include <string>
# include <vector>

////////////////////////////////////////////////////////////////////////////////
/* return value */

extern const int OK;
extern const int ERR;

extern const int GETADDRINFO_SUCCESS;

extern const int ACCEPT_ERROR;
extern const int BIND_ERROR;
extern const int CLOSE_ERROR;
extern const int FCNTL_ERROR;
extern const int LISTEN_ERROR;
extern const int SETSOCKOPT_ERROR;
extern const int SOCKET_ERROR;
extern const int STAT_ERROR;

extern const ssize_t RECV_ERROR;
extern const ssize_t SEND_ERROR;

////////////////////////////////////////////////////////////////////////////////
/* initial value */

extern const int COUNTER_INIT;
extern const int INIT_FD;

extern const double WEIGHT_INIT;

////////////////////////////////////////////////////////////////////////////////

/* num */
extern const int SINGLE_OCCURRENCE_LIMIT;
extern const int PORT_MIN;
extern const int PORT_MAX;

extern const int IO_TIMEOUT;
extern const int FLAG_NONE;

////////////////////////////////////////////////////////////////////////////////
/* status */

extern const int STATUS_OK;
extern const int STATUS_BAD_REQUEST;
extern const int STATUS_SERVER_ERROR;

////////////////////////////////////////////////////////////////////////////////
/* char */

extern const char COLON;
extern const char COMMA;
extern const char DOUBLE_QUOTE;
extern const char EQUAL_SIGN;
extern const char SEMICOLON;
extern const char SINGLE_QUOTE;
extern const char SLASH;

extern const char PATH_DELIM;
extern const char EXTENSION_DELIM;

extern const char ELEMENT_SEPARATOR;

extern const char EMPTY[];
extern const char TIMEOUT[];

extern const char CONFIG_FILE_EXTENSION[];

////////////////////////////////////////////////////////////////////////////////
/* error message */

extern const char INVALID_PATH_ERROR_MSG[];

////////////////////////////////////////////////////////////////////////////////
/* http message */

extern const char DECIMAL_POINT;
extern const char SIGN_PLUS;
extern const char SIGN_MINUS;

extern const char CR;
extern const char HT;
extern const char LF;
extern const char SP;

extern const char CRLF[];

////////////////////////////////////////////////////////////////////////////////
/* method */

extern const char GET_METHOD[];
extern const char POST_METHOD[];
extern const char DELETE_METHOD[];

extern const std::vector<std::string> METHODS;

std::vector<std::string> init_methods();

////////////////////////////////////////////////////////////////////////////////
/* http version */

extern const char HTTP_1_1[];
extern const char HTTP_2_0[];
extern const char HTTP_3_0[];

extern const std::vector<std::string> HTTP_VERSIONS;

std::vector<std::string> init_http_versions();

////////////////////////////////////////////////////////////////////////////////
/* field name */

extern const char ACCEPT[];
extern const char ACCEPT_CH[];
extern const char ACCEPT_CHARSET[];
extern const char ACCEPT_ENCODING[];
extern const char ACCEPT_LANGUAGE[];
extern const char ACCEPT_PATCH[];
extern const char ACCEPT_POST[];
extern const char ACCEPT_RANGES[];
extern const char ACCESS_CONTROL_ALLOW_CREDENTIALS[];
extern const char ACCESS_CONTROL_ALLOW_HEADERS[];
extern const char ACCESS_CONTROL_ALLOW_METHODS[];
extern const char ACCESS_CONTROL_ALLOW_ORIGIN[];
extern const char ACCESS_CONTROL_EXPOSE_HEADERS[];
extern const char ACCESS_CONTROL_MAX_AGE[];
extern const char ACCESS_CONTROL_REQUEST_HEADERS[];
extern const char ACCESS_CONTROL_REQUEST_METHOD[];
extern const char AGE[];
extern const char ALLOW[];
extern const char ALT_SVC[];
extern const char ALT_USED[];
extern const char AUTHORIZATION[];
extern const char CACHE_CONTROL[];
extern const char CLEAR_SITE_DATA[];
extern const char CONNECTION[];
extern const char CONTENT_DISPOSITION[];
extern const char CONTENT_ENCODING[];
extern const char CONTENT_LANGUAGE[];
extern const char CONTENT_LENGTH[];
extern const char CONTENT_LOCATION[];
extern const char CONTENT_RANGE[];
extern const char CONTENT_SECURITY_POLICY[];
extern const char CONTENT_SECURITY_POLICY_REPORT_ONLY[];
extern const char CONTENT_TYPE[];
extern const char COOKIE[];
extern const char CROSS_ORIGIN_EMBEDDER_POLICY[];
extern const char CROSS_ORIGIN_OPENER_POLICY[];
extern const char CROSS_ORIGIN_RESOURCE_POLICY[];
extern const char DATE[];
extern const char ETAG[];
extern const char EXPECT[];
extern const char EXPECT_CT[];
extern const char EXPIRES[];
extern const char FORWARDED[];
extern const char FROM[];
extern const char HOST[];
extern const char IF_MATCH[];
extern const char IF_MODIFIED_SINCE[];
extern const char IF_NONE_MATCH[];
extern const char IF_RANGE[];
extern const char IF_UNMODIFIED_SINCE[];
extern const char KEEP_ALIVE[];
extern const char LAST_MODIFIED[];
extern const char LINK[];
extern const char LOCATION[];
extern const char MAX_FORWARDS[];
extern const char ORIGIN[];
extern const char PERMISSION_POLICY[];
extern const char PROXY_AUTHENTICATE[];
extern const char PROXY_AUTHORIZATION[];
extern const char RANGE[];
extern const char REFERER[];
extern const char RETRY_AFTER[];
extern const char SEC_FETCH_DEST[];
extern const char SEC_FETCH_MODE[];
extern const char SEC_FETCH_SITE[];
extern const char SEC_FETCH_USER[];
extern const char SEC_PURPOSE[];
extern const char SEC_WEBSOCKET_ACCEPT[];
extern const char SERVER[];
extern const char SERVER_TIMING[];
extern const char SERVICE_WORKER_NAVIGATION_PRELOAD[];
extern const char SET_COOKIE[];
extern const char SOURCEMAP[];
extern const char STRICT_TRANSPORT_SECURITY[];
extern const char TE[];
extern const char TIMING_ALLOW_ORIGIN[];
extern const char TRAILER[];
extern const char TRANSFER_ENCODING[];
extern const char UPGRADE[];
extern const char UPGRADE_INSECURE_REQUESTS[];
extern const char USER_AGENT[];
extern const char VARY[];
extern const char VIA[];
extern const char WWW_AUTHENTICATE[];
extern const char X_CUSTOM_HEADER[];

extern const std::vector<std::string> FIELD_NAMES;
extern const std::vector<std::string> MESSAGE_FRAMING_HEADERS;
extern const std::vector<std::string> ROUTING_HEADERS;
extern const std::vector<std::string> REQUEST_MODIFIERS;
extern const std::vector<std::string> AUTHENTICATION_HEADERS;
extern const std::vector<std::string> IGNORE_HEADERS;

std::vector<std::string> init_field_names();
std::vector<std::string> init_message_framing_headers();
std::vector<std::string> init_routing_headers();
std::vector<std::string> init_request_modifiers();
std::vector<std::string> init_authentication_headers();
std::vector<std::string> init_ignore_headers();

////////////////////////////////////////////////////////////////////////////////
/* field value */

extern const char AUTH_SCHEME[];
extern const char AUTH_PARAM[];

extern const char URI_HOST[];
extern const char PORT[];

extern const char RECEIVED_PROTOCOL[];
extern const char RECEIVED_BY[];
extern const char COMMENT[];

extern const char URI_REFERENCE[];

extern const char WEIGHT_KEY[];

////////////////////////////////////////////////////////////////////////////////
/* date */

extern const char GMT[];

extern const char MON[];
extern const char TUE[];
extern const char WED[];
extern const char THU[];
extern const char FRI[];
extern const char SAT[];
extern const char SUN[];

extern const char JAN[];
extern const char FEB[];
extern const char MAR[];
extern const char APR[];
extern const char MAY[];
extern const char JUN[];
extern const char JUL[];
extern const char AUG[];
extern const char SEP[];
extern const char OCT[];
extern const char NOV[];
extern const char DEC[];

extern const int GREGORIAN_CALENDAR;

enum date_format {
	IMF_FIXDATE,
	RFC850_DATE,
	ASCTIME_DATE
};

extern const std::vector<std::string> DAY_NAMES;
extern const std::vector<std::string> MONTHS;

std::vector<std::string> init_day_names();
std::vector<std::string> init_months();

////////////////////////////////////////////////////////////////////////////////
/* sh-tokens */

extern const std::vector<std::string> SH_TOKENS;

std::vector<std::string> init_sh_tokens();
