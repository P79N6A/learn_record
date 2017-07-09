// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef PROTOBUF_message_2eproto__INCLUDED
#define PROTOBUF_message_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_util.h>
// @@protoc_insertion_point(includes)
class LogonRespMessage;
class LogonRespMessageDefaultTypeInternal;
extern LogonRespMessageDefaultTypeInternal _LogonRespMessage_default_instance_;
class UserInfo;
class UserInfoDefaultTypeInternal;
extern UserInfoDefaultTypeInternal _UserInfo_default_instance_;

namespace protobuf_message_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_message_2eproto

enum UserStatus {
  OFFLINE = 0,
  ONLINE = 1
};
bool UserStatus_IsValid(int value);
const UserStatus UserStatus_MIN = OFFLINE;
const UserStatus UserStatus_MAX = ONLINE;
const int UserStatus_ARRAYSIZE = UserStatus_MAX + 1;

enum LogResult {
  LOGON_RESULT_SUCCESS = 0,
  LOGON_RESULT_NOTEXIST = 1,
  LOGON_RESULT_ERROR_PASSWD = 2,
  LOGON_RESULT_ALREADY_LOGON = 3,
  LOGON_RESULT_SERVER_ERROR = 4
};
bool LogResult_IsValid(int value);
const LogResult LogResult_MIN = LOGON_RESULT_SUCCESS;
const LogResult LogResult_MAX = LOGON_RESULT_SERVER_ERROR;
const int LogResult_ARRAYSIZE = LogResult_MAX + 1;

// ===================================================================

class UserInfo : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:UserInfo) */ {
 public:
  UserInfo();
  virtual ~UserInfo();

  UserInfo(const UserInfo& from);

  inline UserInfo& operator=(const UserInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const UserInfo& default_instance();

  static inline const UserInfo* internal_default_instance() {
    return reinterpret_cast<const UserInfo*>(
               &_UserInfo_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(UserInfo* other);

  // implements Message ----------------------------------------------

  inline UserInfo* New() const PROTOBUF_FINAL { return New(NULL); }

  UserInfo* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const UserInfo& from);
  void MergeFrom(const UserInfo& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(UserInfo* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 2;
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required int64 acctID = 1;
  bool has_acctid() const;
  void clear_acctid();
  static const int kAcctIDFieldNumber = 1;
  ::google::protobuf::int64 acctid() const;
  void set_acctid(::google::protobuf::int64 value);

  // required .UserStatus status = 3;
  bool has_status() const;
  void clear_status();
  static const int kStatusFieldNumber = 3;
  ::UserStatus status() const;
  void set_status(::UserStatus value);

  // @@protoc_insertion_point(class_scope:UserInfo)
 private:
  void set_has_acctid();
  void clear_has_acctid();
  void set_has_name();
  void clear_has_name();
  void set_has_status();
  void clear_has_status();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int64 acctid_;
  int status_;
  friend struct protobuf_message_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class LogonRespMessage : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:LogonRespMessage) */ {
 public:
  LogonRespMessage();
  virtual ~LogonRespMessage();

  LogonRespMessage(const LogonRespMessage& from);

  inline LogonRespMessage& operator=(const LogonRespMessage& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const LogonRespMessage& default_instance();

  static inline const LogonRespMessage* internal_default_instance() {
    return reinterpret_cast<const LogonRespMessage*>(
               &_LogonRespMessage_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(LogonRespMessage* other);

  // implements Message ----------------------------------------------

  inline LogonRespMessage* New() const PROTOBUF_FINAL { return New(NULL); }

  LogonRespMessage* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const LogonRespMessage& from);
  void MergeFrom(const LogonRespMessage& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(LogonRespMessage* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .UserInfo UserInfo = 2;
  bool has_userinfo() const;
  void clear_userinfo();
  static const int kUserInfoFieldNumber = 2;
  const ::UserInfo& userinfo() const;
  ::UserInfo* mutable_userinfo();
  ::UserInfo* release_userinfo();
  void set_allocated_userinfo(::UserInfo* userinfo);

  // required .LogResult logonResult = 1;
  bool has_logonresult() const;
  void clear_logonresult();
  static const int kLogonResultFieldNumber = 1;
  ::LogResult logonresult() const;
  void set_logonresult(::LogResult value);

  // @@protoc_insertion_point(class_scope:LogonRespMessage)
 private:
  void set_has_logonresult();
  void clear_has_logonresult();
  void set_has_userinfo();
  void clear_has_userinfo();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::UserInfo* userinfo_;
  int logonresult_;
  friend struct protobuf_message_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// UserInfo

// required int64 acctID = 1;
inline bool UserInfo::has_acctid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UserInfo::set_has_acctid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UserInfo::clear_has_acctid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UserInfo::clear_acctid() {
  acctid_ = GOOGLE_LONGLONG(0);
  clear_has_acctid();
}
inline ::google::protobuf::int64 UserInfo::acctid() const {
  // @@protoc_insertion_point(field_get:UserInfo.acctID)
  return acctid_;
}
inline void UserInfo::set_acctid(::google::protobuf::int64 value) {
  set_has_acctid();
  acctid_ = value;
  // @@protoc_insertion_point(field_set:UserInfo.acctID)
}

// required string name = 2;
inline bool UserInfo::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UserInfo::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UserInfo::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UserInfo::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& UserInfo::name() const {
  // @@protoc_insertion_point(field_get:UserInfo.name)
  return name_.GetNoArena();
}
inline void UserInfo::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserInfo.name)
}
#if LANG_CXX11
inline void UserInfo::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:UserInfo.name)
}
#endif
inline void UserInfo::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserInfo.name)
}
inline void UserInfo::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserInfo.name)
}
inline ::std::string* UserInfo::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:UserInfo.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserInfo::release_name() {
  // @@protoc_insertion_point(field_release:UserInfo.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserInfo::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:UserInfo.name)
}

// required .UserStatus status = 3;
inline bool UserInfo::has_status() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UserInfo::set_has_status() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UserInfo::clear_has_status() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UserInfo::clear_status() {
  status_ = 0;
  clear_has_status();
}
inline ::UserStatus UserInfo::status() const {
  // @@protoc_insertion_point(field_get:UserInfo.status)
  return static_cast< ::UserStatus >(status_);
}
inline void UserInfo::set_status(::UserStatus value) {
  assert(::UserStatus_IsValid(value));
  set_has_status();
  status_ = value;
  // @@protoc_insertion_point(field_set:UserInfo.status)
}

// -------------------------------------------------------------------

// LogonRespMessage

// required .LogResult logonResult = 1;
inline bool LogonRespMessage::has_logonresult() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LogonRespMessage::set_has_logonresult() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LogonRespMessage::clear_has_logonresult() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LogonRespMessage::clear_logonresult() {
  logonresult_ = 0;
  clear_has_logonresult();
}
inline ::LogResult LogonRespMessage::logonresult() const {
  // @@protoc_insertion_point(field_get:LogonRespMessage.logonResult)
  return static_cast< ::LogResult >(logonresult_);
}
inline void LogonRespMessage::set_logonresult(::LogResult value) {
  assert(::LogResult_IsValid(value));
  set_has_logonresult();
  logonresult_ = value;
  // @@protoc_insertion_point(field_set:LogonRespMessage.logonResult)
}

// required .UserInfo UserInfo = 2;
inline bool LogonRespMessage::has_userinfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LogonRespMessage::set_has_userinfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LogonRespMessage::clear_has_userinfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LogonRespMessage::clear_userinfo() {
  if (userinfo_ != NULL) userinfo_->::UserInfo::Clear();
  clear_has_userinfo();
}
inline const ::UserInfo& LogonRespMessage::userinfo() const {
  // @@protoc_insertion_point(field_get:LogonRespMessage.UserInfo)
  return userinfo_ != NULL ? *userinfo_
                         : *::UserInfo::internal_default_instance();
}
inline ::UserInfo* LogonRespMessage::mutable_userinfo() {
  set_has_userinfo();
  if (userinfo_ == NULL) {
    userinfo_ = new ::UserInfo;
  }
  // @@protoc_insertion_point(field_mutable:LogonRespMessage.UserInfo)
  return userinfo_;
}
inline ::UserInfo* LogonRespMessage::release_userinfo() {
  // @@protoc_insertion_point(field_release:LogonRespMessage.UserInfo)
  clear_has_userinfo();
  ::UserInfo* temp = userinfo_;
  userinfo_ = NULL;
  return temp;
}
inline void LogonRespMessage::set_allocated_userinfo(::UserInfo* userinfo) {
  delete userinfo_;
  userinfo_ = userinfo;
  if (userinfo) {
    set_has_userinfo();
  } else {
    clear_has_userinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:LogonRespMessage.UserInfo)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::UserStatus> : ::google::protobuf::internal::true_type {};
template <> struct is_proto_enum< ::LogResult> : ::google::protobuf::internal::true_type {};

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_message_2eproto__INCLUDED
