set(OKI_PROJECT oki-bank)
set(MODELS_PROJECT_FILES 
  src/models/public_account_info.cxx
  src/models/private_account_info.cxx
  src/models/public_user.cxx
  src/models/private_user.cxx
  src/models/transaction.cxx
)
set(SQLITE3_INCLUDE_FILES 
  include/sqlite3/sqlite3.c
)
set(SQLITE3_PROJECT_FILES
  src/database/sqlite/sqlite3_obj.cxx
  src/database/sqlite/exceptions/sqlite_exception.cxx
)