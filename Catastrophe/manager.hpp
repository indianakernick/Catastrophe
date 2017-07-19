//
//  manager.hpp
//  Catastrophe
//
//  Created by Indi Kernick on 18/7/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef manager_hpp
#define manager_hpp

#include <new>
#include <cassert>
#include "entity.hpp"
#include "signature bitsets.hpp"
#include "component storage.hpp"

template <typename Settings>
class Manager {
public:
  static_assert(IsSettings<Settings>::value);
  
  using SigBitsets = SignatureBitsets<Settings>;
  using CompStorage = ComponentStorage<Settings>;
  using Entity = Entity<Settings>;
  using Bitset = typename Settings::Bitset;
  
  Manager() {
    growTo(100);
  }
  ~Manager() {
    clear();
  }
  
  void clear() {
    for (size_t e = 0; e != nextSize; e++) {
      if (entities[e].alive) {
        remAllComps(e);
        entities[e].alive = false;
      }
    }
    
    size = nextSize = 0;
  }
  
  Entity &getEntity(const size_t index) {
    assert(index < nextSize);
    return entities[index];
  }
  const Entity &getEntity(const size_t index) const {
    assert(index < nextSize);
    return entities[index];
  }
  
  bool isAlive(const size_t index) const {
    assert(index < nextSize);
    return entities[index].alive;
  }
  void kill(const size_t index) {
    assert(index < nextSize);
    entities[index].alive = false;
  }
  
private:
  template <typename Tag>
  typename Bitset::reference getTagBit(const size_t index) const {
    static_assert(Settings::template IsTag<Tag>::value);
    assert(index < nextSize);
    return entities[index].bitset[Settings::template tagID<Tag>()];
  }

public:
  template <typename Tag>
  bool hasTag(const size_t index) {
    return getTagBit<Tag>(index);
  }
  template <typename Tag>
  void addTag(const size_t index) {
    getTagBit<Tag>(index) = true;
  }
  template <typename Tag>
  void remTag(const size_t index) {
    getTagBit<Tag>(index) = false;
  }
  
private:
  template <typename Comp>
  typename Bitset::reference getCompBit(const size_t index) const {
    static_assert(Settings::template isComp<Comp>::value);
    assert(index < nextSize);
    return entities[index].bitset[Settings::template compID<Comp>()];
  }

public:
  template <typename Comp>
  bool hasComp(const size_t index) {
    return getCompBit<Comp>(index);
  }
  template <typename Comp, typename ...Args>
  Comp &addComp(const size_t index, Args &&... args) {
    assert(!getCompBit<Comp>(index));
    getCompBit<Comp>(index) = true;
    const size_t compIndex = entities[index].compIndex;
    Comp &comp = std::get<std::vector<Comp>>(components.components)[compIndex];
    new (&comp) Comp(std::forward<Args>(args)...);
    return comp;
  }
  template <typename Comp>
  void remComp(const size_t index) {
    assert(getCompBit<Comp>(index));
    getCompBit<Comp>(index) = false;
    std::get<std::vector<Comp>>(components.components)[entities[index].compIndex].~Comp();
  }
  template <typename Comp>
  Comp &getComp(const size_t index) {
    assert(getCompBit<Comp>(index));
    return components.components[entities[index].compIndex];
  }
  template <typename Comp>
  const Comp &getComp(const size_t index) const {
    assert(getCompBit<Comp>(index));
    return components.components[entities[index].compIndex];
  }
  
  void remAllComps(const size_t index) {
    assert(index < nextSize);
    Entity &entity = entities[index];
    const size_t compIndex = entity.compIndex;
    const Bitset bitset = entity.bitset;
    
    Utils::forEach<typename Settings::Comps>([this, compIndex, bitset] (auto c) {
      using Comp = typename decltype(c)::type;
      if (bitset[Settings::template compID<Comp>()]) {
        std::get<std::vector<Comp>>(components.components)[compIndex].~Comp();
      }
    });
    
    entity.bitset.reset();
  }
  
  size_t makeEntity() {
    growIfNeeded();
    
    const size_t entity = nextSize++;
    
    assert(!entities[entity].alive);
    Entity &e = entities[entity];
    e.alive = true;
    e.bitset.reset();
    e.compIndex = entity;
    
    return entity;
  }
  
private:
  size_t refreshImpl() {
    size_t deadIndex = 0;
    size_t aliveIndex = nextSize - 1;
    
    while (true) {
      while (true) {
        if (deadIndex > aliveIndex) {
          return deadIndex;
        }
        if (!entities[deadIndex].alive) {
          break;
        }
        deadIndex++;
      }
      
      while (true) {
        if (entities[aliveIndex].alive) {
          break;
        }
        if (aliveIndex <= deadIndex) {
          return deadIndex;
        }
        
        aliveIndex--;
      }
      
      assert(!entities[deadIndex].alive);
      assert(entities[aliveIndex].alive);
      
      //deadIndex was killed this update because it is with the live entities
      remAllComps(deadIndex);
      
      std::swap(entities[deadIndex], entities[aliveIndex]);
      
      deadIndex++;
      aliveIndex--;
    }
  }

public:
  void refresh() {
    if (nextSize == size) {
      return;
    }
    size = nextSize = refreshImpl();
  }
  
  template <typename Sig>
  bool matchesSignature(const size_t index) {
    assert(index < nextSize);
    const Bitset entityBitset = entities[index].bitset;
    constexpr Bitset sigBitset = SigBitsets::template getSigBitset<Sig>();
    return (entityBitset & sigBitset) == sigBitset;
  }
  
  template <typename Function>
  void forEachEntity(Function &&function) {
    for (size_t e = 0; e != size; e++) {
      function(e);
    }
  }
  
private:
  template <typename SigComps>
  struct UnpackComponents;
  
  template <typename ...SigComps>
  struct UnpackComponents<Utils::TypeList<SigComps...>> {
    template <typename Function>
    static void call(Manager &manager, const size_t index, Function &&function) {
      assert(index < manager.nextSize);
      const size_t compIndex = manager.entities[index].compIndex;
      function(
        index,
        manager.components.template getComponent<SigComps>(compIndex)...
      );
    }
  };
  
  template <typename SigComps>
  friend struct UnpackComponents;
  
public:
  template <typename Sig, typename Function>
  void forEachEntityMatching(Function &&function) {
    static_assert(Settings::template isSig<Sig>());
  
    for (size_t e = 0; e != size; e++) {
      if (matchesSignature<Sig>(e)) {
        UnpackComponents<typename Settings::template SigComps<Sig>>::call(
          components,
          e,
          std::forward<Function>(function)
        );
      }
    }
  }

private:
  std::vector<Entity> entities;
  CompStorage components;
  size_t capacity = 0;
  size_t size = 0;
  size_t nextSize = 0;
  
  void growTo(const size_t newCapacity) {
    assert(newCapacity > capacity);
    
    entities.resize(newCapacity);
    
    for (size_t e = capacity; e != newCapacity; e++) {
      entities[e].compIndex = e;
    }
    components.growTo(newCapacity);
  }
  
  void growIfNeeded() {
    if (nextSize >= capacity) {
      growTo(capacity * 2);
    }
  }
};

#endif
