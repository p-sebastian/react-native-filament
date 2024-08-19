//
// Created by Marc Rousavy on 16.04.24.
//

#pragma once

#if __has_include(<NitroModules/HybridObject.hpp>)
#include <NitroModules/HybridObject.hpp>
#else
#error NitroModules cannot be found! Are you sure you installed NitroModules properly?
#endif

#include "RNFLogger.h"
#include <memory>
#include <mutex>

namespace margelo {

using namespace facebook;

template <typename T> class PointerHolderNitro {
protected:
  // no default constructor
    PointerHolderNitro() = delete;

  /**
   * Create a new instance of a pointer holder which holds the given shared_ptr.
   * @param name The name of the implementing class, for example "ViewWrapper".
   * @param pointer The pointer this class will hold. It might be released from JS at any point via `release()`.
   */
    PointerHolderNitro(const char* name, std::shared_ptr<T> pointer) : _name(name), _pointer(pointer) {}

  /**
   * Create a new instance of a pointer holder which holds a shared_ptr of the given value.
   * The shared_ptr will be move-constructed.
   * @param name The name of the implementing class, for example "ViewWrapper".
   * @param value The value this class will hold as a shared_ptr. It might be destroyed from JS at any point via `release()`.
   */
    PointerHolderNitro(const char* name, T&& value) : PointerHolderNitro(name, std::make_shared<T>(std::move(value))) {}

  /**
   * Called when the PointerHolder gets automatically destroyed (e.g. via GC) and the shared_ptr will be destroyed.
   */
  ~PointerHolderNitro() {
    if (_pointer != nullptr) {
      Logger::log(TAG, "Automatically releasing %s... (~PointerHolder())", _name.c_str());
    }
  }

protected:
  /**
   * Manually release this reference to the pointer.
   * If there are any other references to this pointer, no memory will be force-deleted.
   */
  virtual void release() {
    std::unique_lock lock(_mutex);

    if (_pointer == nullptr) {
      throw std::runtime_error("Pointer " + _name + " has already been manually released!");
    }
    Logger::log(TAG, "Manually releasing %s... (PointerHolder::release())", _name.c_str());
    _pointer = nullptr;
  }

  /**
   * Get the shared_ptr this class is holding.
   * If it has already been manually released from JS, this method will throw a runtime_error.
   */
  std::shared_ptr<T> pointee() {
    std::unique_lock lock(_mutex);

    if (_pointer == nullptr) {
        throw std::runtime_error("Pointer " + _name + " has already been manually released!");
    }
    return _pointer;
  }

  /**
   * Get if the pointer is still valid and strong.
   */
  bool getIsValid() {
    std::unique_lock lock(_mutex);

    return _pointer != nullptr;
  }
    
protected:
  // Hybrid Setup
//    void loadHybridMethods() override {
//        // load base methods/properties
//        HybridObject::loadHybridMethods();
//        // load custom methods/properties
//        registerHybrids(this, [](nitro::Prototype& prototype) {
//          prototype.registerHybridMethod("release", &PointerHolderNitro::release);
//            prototype.registerHybridGetter("isValid", &PointerHolderNitro::getIsValid);
//        });
//    }

private:
  std::string _name;
  std::shared_ptr<T> _pointer;
  std::mutex _mutex;
  static constexpr auto TAG = "PointerHolder";
};

} // namespace margelo
