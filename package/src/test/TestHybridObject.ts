import { FilamentProxy } from '../native/FilamentProxy'

export function testHybridObject() {
  console.log('------ BEGIN HybridObject tests...')
  // 1. Creation
  console.log('Creating HybridObject...')
  const hybridObject = FilamentProxy.createTestObject()
  console.log('Created HybridObject!')

  // 2. Logging the entire thing as JSON
  console.log(hybridObject)

  // 3. Int Getter & Setter
  console.log(`Int: ${hybridObject.int}`)
  hybridObject.int = 6723
  console.log(`New Int: ${hybridObject.int}`)

  // 4. String Getter & Setter
  console.log(`String: ${hybridObject.string}`)
  hybridObject.string = 'new string value!'
  console.log(`New String: ${hybridObject.string}`)

  // 5. Testing multiple arguments and maps
  const result = hybridObject.multipleArguments(5, true, 'hahah!')
  console.log(`multipleArguments() -> ${JSON.stringify(result)}`)

  // 6. Testing callbacks
  hybridObject.sayHelloCallback(() => 'hello from JS!')
  const getter = hybridObject.getIntGetter()
  console.log(`Int getter: ${getter()}`)

  // 7. Create a new one
  const newObject = hybridObject.createNewHybridObject()
  console.log(`Created new hybrid object!`, newObject)

  console.log('------ END HybridObject tests!')
}
