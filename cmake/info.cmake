set(OKI_PROJECT oki-bank)
set(MODELS_PROJECT_FILES 
  src/models/public_account_info.cxx
  src/models/private_account_info.cxx
  src/models/public_user.cxx
  src/models/private_user.cxx
  src/models/transaction.cxx
)
set(DATABASE_PROJECT_FILES
  src/database/sqlstmt_exception.cxx
  src/database/sqlstmt.cxx
  src/database/sqldb.cxx
)
set(SQLITE3_PROJECT_FILES
  src/database/sqlite/sqlite3_rstmt.cxx
  src/database/sqlite/sqlite3_db.cxx
  src/database/sqlite/exceptions/sqlite_exception.cxx
)
set(OKI_BANK
  src/main.cxx
)
set(OKI_THREAD
  src/thread/okimutex.cxx
)
set(OKI_CACHE
  src/cache/cache_iterator.cxx
  src/cache/base_cache_heap.cxx
  src/cache/cache_controller.cxx
  src/cache/std_cache_controller.cxx
)
set(OKI_CRYPTO
  src/crypto/crypto_base.cxx
  src/crypto/sha256/sha256_block.cxx
  src/crypto/sha256/sha256.cxx
)