import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent'
import type { HostComponent, ViewProps } from 'react-native'

export interface NativeProps extends ViewProps {
  onViewReady?: () => void
  /**
   * Every pixel of the view that is not covered by the Filament scene will be transparent.
   *
   * @note if you use a skybox you should disable this feature.
   *
   * @default true
   */
  enableTransparentRendering?: boolean
}

export const FilamentNativeView = codegenNativeComponent<NativeProps>('FilamentView') as HostComponent<NativeProps>
