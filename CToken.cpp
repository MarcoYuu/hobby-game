#include "CToken.h"


//http://www.s34.co.jp/cpptechdoc/misc/stx-string/

//�R���X�g���N�^
CToken::CToken(const string& str, const string& del, bool ret)
  : cur_(0), str_(str), del_(del), ret_(ret) {}

//�����I�ȃX�L�b�v����
void CToken::skip() 
{
  if ( cur_ == str_.length() )
    cur_ = string::npos;

  if ( !ret_ && cur_ != string::npos ) {
    string::size_type tmp = str_.find_first_not_of(del_, cur_);
    if ( tmp != string::npos )
      cur_ = tmp;
  }
}

//�Ԃ��g�[�N���������Ȃ�true 
bool CToken::empty() 
{
  skip();
  return cur_ == string::npos;
}

//���̃g�[�N����Ԃ�
string CToken::next() 
{
  range_type range = next_range();
  return str_.substr(range.first, range.second);
}


CToken::range_type CToken::next_range() 
{
  skip();
  string::size_type start = cur_;
  string::size_type tmp = cur_;
  if ( cur_ != string::npos ) cur_ = str_.find_first_of(del_,cur_);
  if ( cur_ == string::npos ) return range_type(start,str_.length()-start);
  if ( ret_ && start == cur_ && del_.find(str_[cur_]) != string::npos ) ++cur_;
  return range_type(start,cur_-start);
}

//�������镶������w��
void CToken::set_str(const string& str) 
{
  str_ = str;
  cur_ = 0;
}

//�f���~�^�̐ݒ�
void CToken::set_delimiter(const string& delim, bool ret) 
{
  del_ = delim;
  ret_ = ret;
}

//���݂��ꂩ��Ԃ��\��̃g�[�N����
size_t CToken::count() const 
{
  size_t count = 0;
  string::size_type currpos = cur_;
  while ( currpos != string::npos ) {
    if ( !ret_ ) {
      currpos = str_.find_first_not_of(del_,currpos);
      if ( currpos == string::npos ) { ++count; break; }
    } else if ( currpos == str_.length() ) {
      break;
    }
    string::size_type start = currpos;
    if ( currpos != string::npos ) currpos = str_.find_first_of(del_,currpos);
    if ( currpos == string::npos ) { ++count; break; }
    if ( ret_ && start == currpos && del_.find(str_[currpos]) != string::npos ) ++currpos;
    ++count;
  }
  return count;
}

