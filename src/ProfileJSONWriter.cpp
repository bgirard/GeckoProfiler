/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/HashFunctions.h"

#include "ProfileJSONWriter.h"

void
ChunkedJSONWriteFunc::Write(const char* aStr)
{
  MOZ_ASSERT(mChunkPtr >= mChunkList.back().get() && mChunkPtr <= mChunkEnd);
  MOZ_ASSERT(mChunkEnd >= mChunkList.back().get() + mChunkLengths.back());

  size_t len = strlen(aStr);

  // Most strings to be written are small, but subprocess profiles (e.g.,
  // from the content process in e10s) may be huge. If the string is larger
  // than a chunk, allocate its own chunk.
  char* newPtr;
  if (len >= kChunkSize) {
    AllocChunk(len);
    newPtr = mChunkPtr + len;
  } else {
    newPtr = mChunkPtr + len;
    if (newPtr > mChunkEnd) {
      AllocChunk(kChunkSize);
      newPtr = mChunkPtr + len;
    }
  }

  memcpy(mChunkPtr, aStr, len);
  mChunkPtr = newPtr;
  mChunkLengths.back() += len;
}

mozilla::UniquePtr<char[]>
ChunkedJSONWriteFunc::CopyData() const
{
  MOZ_ASSERT(mChunkLengths.length() == mChunkList.length());
  size_t totalLen = 1;
  for (size_t i = 0; i < mChunkLengths.length(); i++) {
    MOZ_ASSERT(strlen(mChunkList[i].get()) == mChunkLengths[i]);
    totalLen += mChunkLengths[i];
  }
  mozilla::UniquePtr<char[]> c = mozilla::MakeUnique<char[]>(totalLen);
  char* ptr = c.get();
  for (size_t i = 0; i < mChunkList.length(); i++) {
    size_t len = mChunkLengths[i];
    memcpy(ptr, mChunkList[i].get(), len);
    ptr += len;
  }
  *ptr = '\0';
  return c;
}

void
ChunkedJSONWriteFunc::AllocChunk(size_t aChunkSize)
{
  MOZ_ASSERT(mChunkLengths.length() == mChunkList.length());
  mozilla::UniquePtr<char[]> newChunk = mozilla::MakeUnique<char[]>(aChunkSize);
  mChunkPtr = newChunk.get();
  mChunkEnd = mChunkPtr + aChunkSize;
  MOZ_ALWAYS_TRUE(mChunkLengths.append(0));
  MOZ_ALWAYS_TRUE(mChunkList.append(mozilla::Move(newChunk)));
}

void
SpliceableJSONWriter::Splice(const ChunkedJSONWriteFunc* aFunc)
{
  Separator();
  for (size_t i = 0; i < aFunc->mChunkList.length(); i++) {
    WriteFunc()->Write(aFunc->mChunkList[i].get());
  }
  mNeedComma[mDepth] = true;
}

void
SpliceableJSONWriter::Splice(const char* aStr)
{
  Separator();
  WriteFunc()->Write(aStr);
  mNeedComma[mDepth] = true;
}
