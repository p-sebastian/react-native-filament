import * as React from 'react'
import { useCallback, useEffect, useMemo } from 'react'

import { Platform, StyleSheet } from 'react-native'
import { FilamentProxy, FilamentView, Float3, RenderCallback } from 'react-native-filament'

const engine = FilamentProxy.createEngine()

const penguModelPath = Platform.select({
  android: 'custom/pengu.glb',
  ios: 'pengu.glb',
})!

const indirectLightPath = Platform.select({
  android: 'custom/default_env_ibl.ktx',
  ios: 'default_env_ibl.ktx',
})!

const cameraPosition: Float3 = [0, 0, 8]
const cameraTarget: Float3 = [0, 0, 0]
const cameraUp: Float3 = [0, 1, 0]

export default function App() {
  const [_pengu, penguAnimator] = useMemo(() => {
    const modelBuffer = FilamentProxy.getAssetByteBuffer(penguModelPath)
    const asset = engine.loadAsset(modelBuffer)
    const animator = asset.getAnimator()
    asset.releaseSourceData()

    return [asset, animator]
  }, [])

  const renderCallback: RenderCallback = useCallback(
    (_timestamp, _startTime, passedSeconds) => {
      penguAnimator.applyAnimation(0, passedSeconds)
      penguAnimator.updateBoneMatrices()

      engine.getCamera().lookAt(cameraPosition, cameraTarget, cameraUp)
    },
    [penguAnimator],
  )

  // Setup the 3D scene:
  useEffect(() => {
    // TODO: I have to use requestAnimationFrame here, otherwise the view is not yet linked (componentDidMount)
    requestAnimationFrame(() => {
      // Create a default light:
      const indirectLightBuffer = FilamentProxy.getAssetByteBuffer(indirectLightPath)
      engine.setIndirectLight(indirectLightBuffer)

      // Create a directional light for supporting shadows
      const light = engine.createLightEntity('directional', 6500, 10000, 0, -1, 0, true)
      engine.getScene().addEntity(light)

      // Setup camera lens:
      // TODO: Issue, view is only available after we linked the surface hmmm
      const view = engine.getView()
      const aspectRatio = view.aspectRatio
      console.log('aspectRatio', aspectRatio)
      const focalLengthInMillimeters = 28
      const near = 0.1
      const far = 1000
      const camera = engine.getCamera()
      camera.setLensProjection(focalLengthInMillimeters, aspectRatio, near, far)
    })
  }, [])

  return <FilamentView style={styles.filamentView} engine={engine} renderCallback={renderCallback} />
}

const styles = StyleSheet.create({
  filamentView: {
    flex: 1,
    backgroundColor: 'lightblue',
  },
})
