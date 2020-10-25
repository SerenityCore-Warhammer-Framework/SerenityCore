#ifndef SERENITY_REVISIONDATA_HPP
#define SERENITY_REVISIONDATA_HPP

#define _HASH                      "@RevHash@"
#define _DATE                      "@RevDate@"
#define _BRANCH                    "@RevBranch@"
#define _CMAKE_COMMAND             R"(@CMAKE_COMMAND@)"
#define _CMAKE_VERSION             R"(@CMAKE_VERSION@)"
#define _CMAKE_HOST_SYSTEM         R"(@CMAKE_HOST_SYSTEM_NAME@ @CMAKE_HOST_SYSTEM_VERSION@)"
#define _SOURCE_DIRECTORY          R"(@CMAKE_SOURCE_DIR@)"
#define _BUILD_DIRECTORY           R"(@BUILDDIR@)"
#define _MYSQL_EXECUTABLE          R"(@MYSQL_EXECUTABLE@)"
#define _FULL_DATABASE             "SCWOF_DB_FULL_WORLD_VER_DATE.sql"
#define _HOTFIXES_DATABASE         "SCWOF_DB_FULL_HOTFIXES_VER_DATE.sql"
#define VER_COMPANYNAME_STR        "SerenityCore Warhammer Online Framework"
#define VER_LEGALCOPYRIGHT_STR     "(c)2020-2021 SerenityCore"
#define VER_FILEVERSION            0,0,0
#define VER_FILEVERSION_STR        "@rev_hash@ @rev_date@ (@rev_branch@ branch)"
#define VER_PRODUCTVERSION         VER_FILEVERSION
#define VER_PRODUCTVERSION_STR     VER_FILEVERSION_STR

#endif //SERENITY_REVISIONDATA_HPP
