//
//  settings.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 18/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef settings_hpp
#define settings_hpp

#include <bitset>
#include <Simpleton/Utils/type list.hpp>

template <typename ...Comps>
using Components = Utils::TypeList<Comps...>;

template <typename ...Tags>
using Tags = Utils::TypeList<Tags...>;

template <typename ...CompsOrTags>
using Signature = Utils::TypeList<CompsOrTags...>;

template <typename ...Sigs>
using Signatures = Utils::TypeList<Sigs...>;

template <typename Comps0, typename Tags0, typename Sigs0>
struct Settings {
  using Comps = Comps0;
  using Tags = Tags0;
  using Sigs = Sigs0;
  
  //A type is a component if it is contained in the component list
  template <typename Comp>
  using IsComp = std::integral_constant<bool, Utils::listContains<Comps, Comp>>;
  
  //A type is a tag if it is contained in the tag list
  template <typename Tag>
  using IsTag = std::integral_constant<bool, Utils::listContains<Tags, Tag>>;
  
  //The components of a signature
  template <typename Sig>
  using SigComps = Utils::FilterList<Sig, IsComp>;
  
  //The tags of a signature
  template <typename Sig>
  using SigTags = Utils::FilterList<Sig, IsTag>;
  
  //A signature must be a list of components and tags
  template <typename Sig>
  using ValidSig = std::integral_constant<bool,
    Utils::listSize<SigComps<Sig>> +
    Utils::listSize<SigTags<Sig>> ==
    Utils::listSize<Sig>
  >;
  
  //the number of valid signatures is equal to the number of signatures
  static_assert(
    Utils::listSize<Utils::FilterList<Sigs, ValidSig>> ==
    Utils::listSize<Sigs>
  );
  
  //the bitset will contain a bit for every component and tag
  static constexpr size_t BITSET_SIZE = Utils::listSize<Comps> + Utils::listSize<Tags>;
  
  using Bitset = std::bitset<BITSET_SIZE>;
  
  //The bit that corresponds to the component
  template <typename Comp>
  static constexpr size_t compID() {
    static_assert(Settings::template IsComp<Comp>::value);
    return Utils::indexOf<Comps, Comp>;
  }
  
  //The bit that corresponds to the tag
  template <typename Tag>
  static constexpr size_t tagID() {
    static_assert(Settings::template IsTag<Tag>::value);
    return Utils::listSize<Comps> + Utils::indexOf<Tags, Tag>;
  }
};

template <typename Settings>
struct IsSettings {
  static constexpr bool value = false;
};

template <typename Comps, typename Tags, typename Sigs>
struct IsSettings<Settings<Comps, Tags, Sigs>> {
  static constexpr bool value = true;
};

#endif
