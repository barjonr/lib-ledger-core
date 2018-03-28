// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from amount.djinni

#import "LGCurrency.h"
#import "LGCurrencyUnit.h"
#import "LGFormatRules.h"
#import "LGLocale.h"
#import <Foundation/Foundation.h>
@class LGAmount;
@class LGBigInt;


@interface LGAmount : NSObject

- (nullable LGBigInt *)toBigInt;

- (nonnull LGCurrency *)getCurrency;

- (nonnull LGCurrencyUnit *)getUnit;

- (nullable LGAmount *)toUnit:(nonnull LGCurrencyUnit *)unit;

- (nullable LGAmount *)toMagnitude:(int32_t)magnitude;

- (nonnull NSString *)toString;

- (int64_t)toLong;

- (double)toDouble;

- (nonnull NSString *)format:(nonnull LGLocale *)locale
                       rules:(nullable LGFormatRules *)rules;

+ (nullable LGAmount *)fromHex:(nonnull LGCurrency *)currency
                           hex:(nonnull NSString *)hex;

+ (nullable LGAmount *)fromLong:(nonnull LGCurrency *)currency
                          value:(int64_t)value;

@end
