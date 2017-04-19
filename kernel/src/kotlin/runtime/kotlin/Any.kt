package kotlin


public open class Any {

    external public open operator fun equals(other: Any?): Boolean

    external public open fun hashCode(): Int

    external public open fun toString(): String
}

public fun Any?.hashCode() = if (this != null) this.hashCode() else 0
