#ifndef BYTECODE_H_
#define BYTECODE_H_

#include "register.h"

#include <string>
#include <iostream>


#define I InstructionKind::

typedef unsigned long ul;
typedef long l;
typedef unsigned int ui;
typedef short s;

enum AddrMod : unsigned short {
  _Imm,
  _Adr,
  _Reg,
  _Idx
};

static std::string addr_mod[] = {
  "Imm",
  "Adr",
  "Reg",
  "Idx"
};

#define X(A)                       \
  A(NONE),                         \
  A(LDAI),                         \
  A(LDADR),                        \
  A(LDAKEY),                       \
  A(LDAARR),                       \
  A(LDAOBJ),                       \
  A(LDANUM),                       \
  A(LDASTR),                       \
  A(STRR),                         \
  A(STRA),                         \
  A(RESIZEARR),                    \
  A(PUSHI),                        \
  A(PUSHADR),                      \
  A(PUSHREG),                      \
  A(OPUSHOBJ),                     \
  A(OPUSHARR),                     \
  A(PUSHKEY),                      \
  A(POPADR),                       \
  A(POPA),                         \
  A(POPKEY),                       \
  A(POPTOARR),                     \
  A(POPTOOBJ),                     \
  A(OPOPTS),                       \
  A(OPOPTARR),                     \
  A(OPOPTOBJ),                     \
  A(EMPTY),                        \
  A(ADD),                          \
  A(SUB),                          \
  A(MUL),                          \
  A(DIV),                          \
  A(MOD),                          \
  A(SHR),                          \
  A(SHL),                          \
  A(EQ),                           \
  A(NEQ),                          \
  A(LT),                           \
  A(GT),                           \
  A(JMP),                          \
  A(JMPZ),                         \
  A(CALL),                         \
  A(RET),                          \
  A(HLT)

#define V(x) x

enum class Instruction {
  X(V)
};

#undef V

#define S(a) { #a }

static std::string _instructions_[] = {
  X(S)
};

#undef S

class Bytecode {
public:
  Bytecode(Instruction instruction,
           const Register &value)
    : instruction_(static_cast<ui>(instruction)),
    value_(value) {
  }

  Bytecode(Instruction instruction)
    : instruction_(static_cast<ui>(instruction)),
    value_(Register()) {
  }

  Bytecode(ui instruction,
           const Register &value)
    : instruction_((instruction)),
    value_(value) {
  }

  Bytecode(ui instruction)
    : instruction_((instruction)),
    value_(Register()) {
  }

  Bytecode()
    : instruction_(static_cast<ui>(Instruction::NONE)) {
  }

  ~Bytecode() = default;

  Bytecode(const Bytecode &rhs) = default;

  Bytecode &operator=(const Bytecode &rhs) = default;

  void print(std::ostream &os)  const {
    os << _instructions_[(int)instruction_] << "\t";
    value_.print(os);
  };

  unsigned int instruction_;
  Register value_;
};

// all static
namespace B {
typedef Instruction i;

static Bytecode none() {
  return Bytecode();
}

static Bytecode ldai(Register imm) {
  return Bytecode((static_cast<int>(i::LDAI)), imm);
}

static Bytecode ldadr(Register reg) {
  return Bytecode((static_cast<ui>(i::LDADR)), reg);
}

static Bytecode ldakey(Register reg) {
  return Bytecode(static_cast<ui>(i::LDAKEY), reg);
}
 
static Bytecode poptoarr() {
  return Bytecode(static_cast<ui>(i::POPTOARR));
}

static Bytecode ldaarr() {
  return Bytecode(static_cast<ui>(i::LDAARR));
}

static Bytecode ldaobj() {
  return Bytecode(static_cast<ui>(i::LDAOBJ));
}

static Bytecode ldanum() {
  return Bytecode(static_cast<ui>(i::LDANUM));
}

static Bytecode ldastr() {
  return Bytecode(static_cast<ui>(i::LDASTR));
}

static Bytecode strr(Register adr) {
  return Bytecode(static_cast<ui>(i::STRR), adr);
}

static Bytecode resizearr(Register adr) {
  return Bytecode(static_cast<ui>(i::RESIZEARR), adr);
}

static Bytecode pushi(Register imm) {
  return Bytecode(static_cast<ui>(i::PUSHI), imm);
}

static Bytecode pushadr(Register imm) {
  return Bytecode(static_cast<ui>(i::PUSHADR), imm);
}

static Bytecode pushreg() {
  return Bytecode(static_cast<ui>(i::PUSHREG));
}

static Bytecode pushkey(Register reg) {
  return Bytecode(static_cast<ui>(i::PUSHKEY), reg);
}

static Bytecode popadr(Register adr) {
  return Bytecode(static_cast<ui>(i::POPADR), adr);
}

static Bytecode popkey(Register key) {
  return Bytecode(static_cast<ui>(i::POPKEY), key);
}

static Bytecode poptoobj(Register key) {
  return Bytecode(static_cast<ui>(i::POPTOOBJ), key);
}

static Bytecode opushobj() {
  return Bytecode(static_cast<ui>(i::OPUSHOBJ));
}

static Bytecode opusharr() {
  return Bytecode(static_cast<ui>(i::OPUSHARR));
}

static Bytecode opoptarr() {
  return Bytecode(static_cast<ui>(i::OPOPTARR));
}

static Bytecode opopts() {
  return Bytecode(static_cast<ui>(i::OPOPTS));
}

static Bytecode opoptobj(Register key) {
  return Bytecode(static_cast<ui>(i::OPOPTOBJ), key);
}

static Bytecode popa() {
  return Bytecode(static_cast<ui>(i::POPA));
}

#define FUNC(name, X)                    \
  static Bytecode name() {                    \
    return Bytecode(static_cast<ui>(i::X));                    \
  }

FUNC(add, ADD);
FUNC(sub, SUB);
FUNC(mul, MUL);
FUNC(div, DIV);
FUNC(mod, MOD);
FUNC(shr, SHR);
FUNC(shl, SHL);
FUNC(equal, EQ);
FUNC(_not_eq, NEQ);
FUNC(lt, LT);
FUNC(gt, GT);

#undef FUNC

static Bytecode jmp(Register j) {
  return Bytecode(static_cast<ui>(i::JMP), Register(j));
}

static Bytecode jmpz() {
  return Bytecode(static_cast<ui>(i::JMPZ));
}

static Bytecode call() {
  // unimplemented
  return Bytecode();
}

static Bytecode ret() {
  return Bytecode(i::RET);
}

static Bytecode empty() {
  return Bytecode(i::EMPTY);
}

static Bytecode hlt() {
  return Bytecode(i::HLT);
}
}

#undef I
#endif // BYTECODE_H_
