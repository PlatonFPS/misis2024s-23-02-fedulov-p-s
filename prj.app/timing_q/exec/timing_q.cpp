#pragma once

#include<decorator/decorator.hpp>

#include<queuelstt/queuelstt.hpp>
#include<queuearrt/queuearrt.hpp>

#include<iostream>
#include<string>

template <class T>
void CtorTest(const int repetitionCount) {
  for (int i = 0; i < repetitionCount; i += 1) {
    T type();
  }
}

template <class T>
void CopyCtorTest(const T& copy) {
  T type(copy);
}
template <class T>
void RValueCopyCtorTest(T& copy) {
  T type(std::move(copy));
}

template <class T>
void AssignmentTest(const T& copy) {
  T type;
  type = copy;
}

template <class T>
void RValueAssignmentTest(T& copy) {
  T type;
  type = std::move(copy);
}

template <class T>
void PushTestLst(const int repetitionCount) {
  QueueLstT<T> queue;
  for (int i = 0; i < repetitionCount; i += 1) {
    queue.Push(i);
  }
}
  
template <class T>
void PushTestArr(const int repetitionCount) {
  QueueArrT<T> queue;
  for (int i = 0; i < repetitionCount; i += 1) {
    queue.Push(i);
  }
}

template <class T>
void PopTestLst(QueueLstT<T>& queue) {
  while(!queue.IsEmpty()) {
    queue.Pop();
  }
}

template <class T>
void PopTestArr(QueueArrT<T>& queue) {
  while(!queue.IsEmpty()) {
    queue.Pop();
  }
}

int main() {
  const int kMinCount = 1;
  const int kMaxCount = 1e6;
  const int kKoef = 10;


  std::cout << "Ctor test\n" << "QueueLstT<int> | QueueArrT<int>\n";
  Decorator queueLstCtor(&CtorTest<QueueLstT<int>>);
  Decorator queueArrCtor(&CtorTest<QueueArrT<int>>);
  for (int i = kMinCount; i <= kMaxCount; i *= kKoef) {
    std::cout << i << ": ";
    std::cout << queueLstCtor.MeasureTime(i) << " | ";
    std::cout << queueArrCtor.MeasureTime(i) << '\n';
  }

  std::cout << "Copy ctor test\n" << "QueueLstT<int> | QueueArrT<int>\n";
  Decorator queueLstCopyCtor(&CopyCtorTest<QueueLstT<int>>);
  Decorator queueArrCopyCtor(&CopyCtorTest<QueueArrT<int>>);
  for (int i = kMinCount; i <= kMaxCount; i *= kKoef) {
    std::cout << i << ": ";
    QueueLstT<int> queueLst;
    QueueArrT<int> queueArr;
    for (int j = 0; j < i; j += 1) {
      queueLst.Push(j);
      queueArr.Push(j);
    }
    std::cout << queueLstCopyCtor.MeasureTime(queueLst) << " | ";
    std::cout << queueArrCopyCtor.MeasureTime(queueArr) << '\n';
  }

  std::cout << "RValue copy ctor test\n" << "QueueLstT<int> | QueueArrT<int>\n";
  Decorator queueLstRValueCtor(&RValueCopyCtorTest<QueueLstT<int>>);
  Decorator queueArrRValueCtor(&RValueCopyCtorTest<QueueArrT<int>>);
  for (int i = kMinCount; i <= kMaxCount; i *= kKoef) {
    std::cout << i << ": ";
    QueueLstT<int> queueLst;
    QueueArrT<int> queueArr;
    for (int j = 0; j < i; j += 1) {
      queueLst.Push(j);
      queueArr.Push(j);
    }
    std::cout << queueLstRValueCtor.MeasureTime(queueLst) << " | ";
    std::cout << queueArrRValueCtor.MeasureTime(queueArr) << '\n';
  }

  std::cout << "Assignment test\n" << "QueueLstT<int> | QueueArrT<int>\n";
  Decorator queueLstAssignment(&AssignmentTest<QueueLstT<int>>);
  Decorator queueArrAssignment(&AssignmentTest<QueueArrT<int>>);
  for (int i = kMinCount; i <= kMaxCount; i *= kKoef) {
    std::cout << i << ": ";
    QueueLstT<int> queueLst;
    QueueArrT<int> queueArr;
    for (int j = 0; j < i; j += 1) {
      queueLst.Push(j);
      queueArr.Push(j);
    }
    std::cout << queueLstAssignment.MeasureTime(queueLst) << " | ";
    std::cout << queueArrAssignment.MeasureTime(queueArr) << '\n';
  }

  std::cout << "RValue assignment test\n" << "QueueLstT<int> | QueueArrT<int>\n";
  Decorator queueLstRValueAssignment(&RValueAssignmentTest<QueueLstT<int>>);
  Decorator queueArrRValueAssignment(&RValueAssignmentTest<QueueArrT<int>>);
  for (int i = kMinCount; i <= kMaxCount; i *= kKoef) {
    std::cout << i << ": ";
    QueueLstT<int> queueLst;
    QueueArrT<int> queueArr;
    for (int j = 0; j < i; j += 1) {
      queueLst.Push(j);
      queueArr.Push(j);
    }
    std::cout << queueLstRValueAssignment.MeasureTime(queueLst) << " | ";
    std::cout << queueArrRValueAssignment.MeasureTime(queueArr) << '\n';
  }

  std::cout << "Push test\n" << "QueueLstT<int> | QueueArrT<int>\n";
  Decorator queueLstPush(&PushTestLst<int>);
  Decorator queueArrPush(&PushTestArr<int>);
  for (int i = kMinCount; i <= kMaxCount; i *= kKoef) {
    std::cout << i << ": ";
    std::cout << queueLstPush.MeasureTime(i) << " | ";
    std::cout << queueArrPush.MeasureTime(i) << '\n';
  }

  std::cout << "Pop test\n" << "QueueLstT<int> | QueueArrT<int>\n";
  Decorator queueLstPop(&PopTestLst<int>);
  Decorator queueArrPop(&PopTestArr<int>);
  for (int i = kMinCount; i <= kMaxCount; i *= kKoef) {
    std::cout << i << ": ";
    QueueLstT<int> queueLst;
    QueueArrT<int> queueArr;
    for(int j = 0; j < i; j += 1) {
      queueLst.Push(j);
      queueArr.Push(j);
    }
    std::cout << queueLstPop.MeasureTime(queueLst) << " | ";
    std::cout << queueArrPop.MeasureTime(queueArr) << '\n';
  }


  return 0;
}