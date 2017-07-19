//
//  signature bitsets.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 18/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef signature_bitsets_hpp
#define signature_bitsets_hpp

#include "settings.hpp"

template <typename Settings>
struct SignatureBitsets {
  static_assert(IsSettings<Settings>::value);

  using Bitset = typename Settings::Bitset;
  using Comps = typename Settings::Comps;
  using Tags = typename Settings::Tags;
  using Sigs = typename Settings::Signatures;
  template <typename Sig>
  using SigComps = typename Settings::template SigComps<Sig>;
  template <typename Sig>
  using SigTags = typename Settings::template SigTags<Sig>;
  
  //The index of the bitset in the tuple that corresponds the signature
  template <typename Sig>
  static constexpr size_t sigID() {
    static_assert(Settings::template isSig<Sig>::value);
    return Utils::indexOf<Sigs, Sig>;
  }
  
  template <typename Sig>
  static constexpr Bitset getSigBitset() {
    return std::get<sigID<Sig>()>(BITSETS);
  }
  
  //There is a bitset of every signature stored in a tuple
  using Bitsets = Utils::UnpackInto<
    Utils::RepeatType<Bitset, Utils::listSize<Sigs>>,
    std::tuple
  >;
  
  static constexpr Bitsets initBitsets() {
    Bitsets bitsets;
    
    //For each signature
    Utils::forEach<Sigs>([&bitsets] (auto s) {
      using Sig = typename decltype(s)::type;
      //For each component in the signature
      Utils::forEach<SigComps>([&bitsets] (auto c) {
        using Comp = typename decltype(c)::type;
        std::get<sigID<Sig>()>(bitsets)[Settings::template compID<Comp>()] = true;
      });
      
      //For each tag in the signature
      Utils::forEach<SigTags>([&bitsets] (auto t) {
        using Tag = typename decltype(t)::type;
        std::get<sigID<Sig>()>(bitsets)[Settings::template tagID<Tag>()] = true;
      });
    });
    
    return bitsets;
  }
  
  static constexpr Bitsets BITSETS = initBitsets();
};

#endif
